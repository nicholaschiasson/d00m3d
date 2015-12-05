#include "particle_engine.h"
ParticleEngine::ParticleEngine()
{
}

ParticleEngine::~ParticleEngine()
{

}

void ParticleEngine::initialize(Ogre::SceneManager* scene_manager, PhysicsEngine& physics_engine)
{
	sceneManager = scene_manager;
	physicsEngine = &physics_engine;

	createSphereParticleGeometry();
	createPlasmaSplineControlPoints();
	createConeParticleGeometry();
}

void ParticleEngine::createSphereParticleGeometry(int numParticles)
{
	Ogre::String object_name = "sphereParticle";
	/* Retrieve scene manager and root scene node */
    Ogre::SceneNode* root_scene_node = sceneManager->getRootSceneNode();

    /* Create the 3D object */
    Ogre::ManualObject* object = NULL;
    object = sceneManager->createManualObject(object_name);
    object->setDynamic(false);

    /* Create point list for the object */
	object->begin("", Ogre::RenderOperation::OT_POINT_LIST);

	/* Create a set of points which will be the particles */
	/* This is similar to drawing a sphere: we will sample points on a sphere, but will allow them to also
		deviate a bit from the sphere along the normal (change of radius) */
	float trad = 1.0f; // Defines the starting point of the particles
    float maxspray = 0.5f; // This is how much we allow the points to deviate from the sphere
	float u, v, w, theta, phi, spray; // Work variables
	for (int i = 0; i < numParticles; i++){
			
		// Randomly select three numbers to define a point in spherical coordinates
		u = ((float) rand() / ((float)RAND_MAX));
        v = ((float) rand() / ((float)RAND_MAX));
        w = ((float) rand() / ((float)RAND_MAX));

		// Use u to define the angle theta along one direction of a sphere
        theta = u * 2.0f * 3.1416f;
		// Use v to define the angle phi along the other direction of the sphere
		phi = acos(2.0f*v - 1.0f);
		// Use we to define how much we can deviate from the surface of the sphere (change of radius)
        spray = maxspray*pow((float) w, (float) (1.0f/3.0f)); // Cubic root of w

		// Define the normal and point based on theta, phi and the spray
        Ogre::Vector3 normal = Ogre::Vector3(spray*cos(theta)*sin(phi), spray*sin(theta)*sin(phi), spray*cos(phi));
		object->position(normal.x*trad, normal.y*trad,normal.z*trad);
		object->normal(normal);
		object->textureCoord(0,0,0);
		object->colour(Ogre::ColourValue(i/(float) numParticles, 0.0f, 1.0f - (i/(float) numParticles))); // We can use the color for debug, if needed
	}
		
	/* We finished the object */
    object->end();
		
    /* Convert triangle list to a mesh */
    object->convertToMesh(object_name);
}

void ParticleEngine::createPlasmaSplineControlPoints(int numControlPoints)
{
	// Control points for the spline
	Ogre::Vector3 *control_point;

	/* Allocate memory for control points */
	control_point = new Ogre::Vector3[numControlPoints];

	/* Create control points of a piecewise spline */
	/* We store the control points in groups of 4 */
	/* Each group represents the control points (p0, p1, p2, p3) of a cubic Bezier curve */
	/* To ensure C1 continuity, we constrain the first and second point of each curve according to the previous curve */
        
	float length = 3.0f;

	// Initialize the first two control points to fixed values */
	control_point[0] = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	control_point[1] = Ogre::Vector3(0.0f, 0.0f, 0.0f);
		
	int j = 0;
	// Create remaining points
	for (int i = 2; i < numControlPoints - 2; i++){
		// Check if we have the first or second point of a curve
		// Then we need to constrain the points
		if (i % 4 == 0){
			// Constrain the first point of the curve
			// p3 = q0, where the previous curve is (p0, p1, p2, p3) and the current curve is (q0, q1, q2, q3)
			// p3 is at position -1 from the current point q0
			control_point[i] = control_point[i - 1];
		} else if (i % 4 == 1){
			// Constrain the second point of the curve
			// q1 = 2*p3 – p2
			// p3 is at position -1 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
			// p2 is at position -2 and we add another -1 since we are at i%4 == 1 (not i%4 == 0)
			control_point[i] = 2.0f*control_point[i - 2] - control_point[i - 3];
		} else {
			// Other points: we can freely assign random values to them
			// Get 3 random numbers
			float px = cos((Ogre::Math::TWO_PI / ((float)numControlPoints / 2.0f)) * j * 4) * 0.5f;
			float py = sin((Ogre::Math::TWO_PI / ((float)numControlPoints / 2.0f)) * j * 4) * 0.5f;
			float pz = (length * ((float)i / (float)numControlPoints)) - (length / 2.0f);
			// Define control points based on u, v, and w and scale by the control point index
			control_point[i] = Ogre::Vector3(px, py, pz);
			++j;
			//control_point[i] = Ogre::Vector3(u*3.0*(i/4 + 1), v*3.0*(i/4+1), 0.0); // Easier to visualize with the control points on the screen
		}
	}
		
	control_point[numControlPoints - 2] = Ogre::Vector3(0.0f, 0.0f, length / 2.0f);
	control_point[numControlPoints - 1] = Ogre::Vector3(0.0f, 0.0f, 0.0f);

	/* Add control points to the material's shader */
	/* Translate the array of Ogre::Vector3 to an accepted format */
	float *shader_data;
	shader_data = new float[numControlPoints*4];
	for (int i = 0; i < numControlPoints; i++){
		shader_data[i*4] = control_point[i].x;
		shader_data[i*4 + 1] = control_point[i].y;
		shader_data[i*4 + 2] = control_point[i].z;
		shader_data[i*4 + 3] = 0.0;
	}

	/* Add array as a parameter to the shader of the specified material */
	Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("SplineParticleMaterial"));
	mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("control_point", shader_data, numControlPoints, 4);

	/* Also create a mesh out of the control points, so that we can render them, if needed */
    Ogre::ManualObject* object = sceneManager->createManualObject("plasmaSplineControlPoints");
    object->setDynamic(false);
	object->begin("", Ogre::RenderOperation::OT_POINT_LIST);
	for (int i = 0; i < numControlPoints; i++){
		object->position(control_point[i]);
		// Color allows us to keep track of control point ordering
		object->colour(1.0f - ((float) i)/((float)numControlPoints), 0.0f, ((float) i)/((float)numControlPoints));
	}
	object->end();
    object->convertToMesh("plasmaSplineControlPoints");

	/* Free memory we used to store control points temporarily */
	delete [] control_point;
}

void ParticleEngine::createConeParticleGeometry(int num_particles){
	
	Ogre::String object_name = "coneParticle";
	/* Retrieve scene manager and root scene node */
    Ogre::SceneNode* root_scene_node = sceneManager->getRootSceneNode();

    /* Create the 3D object */
    Ogre::ManualObject* object = NULL;
    object = sceneManager->createManualObject(object_name);
    object->setDynamic(false);

    /* Create point list for the object */
	object->begin("", Ogre::RenderOperation::OT_POINT_LIST);

	/* Create a set of points which will be the particles */
	float theta, spread, length;
	Ogre::Vector3 vertex_position;
	Ogre::Vector3 vertex_normal;
	Ogre::ColourValue vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < num_particles; i++)
	{
		theta = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
		spread = Ogre::Math::RangeRandom(0.0f, 0.5f);
		length = Ogre::Math::RangeRandom(0.0f, 1.0f);

		vertex_position = 0.5f * Ogre::Vector3(cos(theta), 0.0f, sin(theta));
		vertex_position *= spread;
		vertex_position.y = 1.0f;
		vertex_position *= length;
		vertex_normal = vertex_position.normalisedCopy();

		object->position(vertex_position);
		object->normal(vertex_normal);
		object->colour(Ogre::ColourValue(i/(float) num_particles, 0.0, 1.0f - (i/(float) num_particles))); // We can use the color for debug, if needed
	}
		
	/* We finished the object */
    object->end();
		
    /* Convert triangle list to a mesh */
    object->convertToMesh(object_name);
}

ParticleEffect *ParticleEngine::createParticleEffect(EFFECT_TYPE effect, Ogre::SceneNode* parentNode, Ogre::Vector3 position, Ogre::Vector3 scale)
{
	std::string material_name;
	std::string object_name;
	float duration;
	ParticleEffect* particleEffect = NULL;
	switch(effect){
	case EFFECT_EXPLOSION:
		material_name = "ExplosionMaterial";
		object_name = "sphereParticle";
		duration = 4.0f;
		break;
	case EFFECT_PLASMA:
		material_name = "SplineParticleMaterial";
		object_name = "plasmaSplineControlPoints";
		duration = 6.0f;
	case EFFECT_IDLE_THRUSTER:
		material_name = "FlameParticleMaterial";
		object_name = "sphereParticle";
		duration = -1.0f;
		break;
	case EFFECT_THRUSTER:
		material_name = "FlameParticleMaterial";
		object_name = "coneParticle";
		duration = -1.0f;
	default:
		std::cerr << "Particle Effect Not Found... Creation unsuccessful" << std::endl;
		break;
	}

	particleEffect = new ParticleEffect(sceneManager, parentNode, object_name, material_name, *physicsEngine, duration);
	particleEffect->scale(scale);
	particleEffect->translate(position);
	particles.push_back(particleEffect);
	return particleEffect;
}

void ParticleEngine::update(const Ogre::FrameEvent& fe)
{
	bool cleanup = false;
	for(std::vector<ParticleEffect*>::iterator it = particles.begin(); it != particles.end(); ++it){
		(*it)->Update(fe);
		if(!(*it)->isAlive()){
			cleanup = true;
		}
	}

	if(cleanup){
		cleanupParticles();
	}
}

void ParticleEngine::addParticleEffect(ParticleEffect *particleEffect)
{
	particles.push_back(particleEffect);
}

void ParticleEngine::cleanupParticles()
{
	ParticleEffect* deadParticle = NULL;
	std::vector<ParticleEffect*>::iterator iter = particles.begin();
	while(iter != particles.end()){
		if((*iter)->isAlive()){
			++iter;
			continue;
		}

		//we need to delete if they are not alive.
		deadParticle = (*iter);
		iter = particles.erase(iter);
		deadParticle->cleanup(*physicsEngine);
		delete deadParticle;
		deadParticle = NULL;
	}
}