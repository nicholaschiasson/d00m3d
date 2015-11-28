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

	createExplosionGeometry();
}

void ParticleEngine::createExplosionGeometry(int numParticles)
{
	Ogre::String object_name = "explosion";
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

void ParticleEngine::createParticleEffect(EFFECT_TYPE effect, Ogre::SceneNode* parentNode, Ogre::Vector3 position, Ogre::Vector3 scale)
{
	std::string material_name;
	std::string object_name;
	ParticleEffect* particleEffect = NULL;
	switch(effect){
	case EFFECT_EXPLOSION:
		material_name = "ExplosionMaterial";
		object_name = "explosion";
		break;
	default:
		std::cerr << "Particle Effect Not Found... Creation unsuccessful" << std::endl;
		break;
	}

	particleEffect = new ParticleEffect(sceneManager, parentNode, object_name,material_name, *physicsEngine);
	particleEffect->scale(scale);
	particleEffect->translate(position);
	particles.push_back(particleEffect);
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