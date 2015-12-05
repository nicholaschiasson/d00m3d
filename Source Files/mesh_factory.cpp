#include "mesh_factory.h"

std::auto_ptr<Ogre::Root> *MeshFactory::ogre_root_ = 0;

void MeshFactory::Initialize(std::auto_ptr<Ogre::Root> *root)
{
	ogre_root_ = root;
	CreateCubeGeometry();
	CreateConeGeometry();
	CreateConeGeometry("Pyramid", 4);
	CreateCylinderGeometry();
	CreateCylinderGeometry("OctCylinder", 8);
	CreateTorusGeometry();
	CreateSphereGeometry();
	CreateSemisphereGeometry();
	CreateSemisphereGeometry("SphereScreen", 0.4f);
	CreateUnculledSemisphereGeometry();
	CreateUnculledSemisphereGeometry("HoverShield", 0.1f);
	CreateIcosahedron();
}

void MeshFactory::CreateCubeGeometry(Ogre::String object_name)
{
	try
	{
		/* Retrieve scene manager and root scene node */
		Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create the 3D object */
		Ogre::ManualObject* object = NULL;
		object = scene_manager->createManualObject(object_name);
		object->setDynamic(false);

		/* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float widthBy2 = 0.5f;
		float heightBy2 = 0.5f;
		float depthBy2 = 0.5f;
		Ogre::Vector3 vertexNormal;
		Ogre::ColourValue vertexColor = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);
		Ogre::Vector2 bottomLeft = Ogre::Vector2(0.0f, 0.0f);
		Ogre::Vector2 bottomRight = Ogre::Vector2(1.0f, 0.0f);
		Ogre::Vector2 TopRight = Ogre::Vector2(1.0f, 1.0f);
		Ogre::Vector2 TopLeft = Ogre::Vector2(0.0f, 1.0f);
		
		vertexNormal = (Ogre::Vector3(0.0f, 0.0f, 1.0f));
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(-widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);
		
		vertexNormal = (Ogre::Vector3(0.0f, 0.0f, -1.0f));
		object->position(Ogre::Vector3(widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(-widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);
		
		vertexNormal = (Ogre::Vector3(1.0f, 0.0f, 0.0f));
		object->position(Ogre::Vector3(widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);
		
		vertexNormal = (Ogre::Vector3(-1.0f, 0.0f, 0.0f));
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(-widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(-widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);
		
		vertexNormal = (Ogre::Vector3(0.0f, 1.0f, 0.0f));
		object->position(Ogre::Vector3(-widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(widthBy2, heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(-widthBy2, heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);
		
		vertexNormal = (Ogre::Vector3(0.0f, -1.0f, 0.0f));
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomLeft);
		object->position(Ogre::Vector3(widthBy2, -heightBy2, -depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(bottomRight);
		object->position(Ogre::Vector3(widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopRight);
		object->position(Ogre::Vector3(-widthBy2, -heightBy2, depthBy2));
		object->normal(vertexNormal);
		object->colour(vertexColor);
		object->textureCoord(TopLeft);

		for (int i = 0; i < (4 * 6); i += 4)
		{
			object->triangle(i, i + 1, i + 2);
			object->triangle(i, i + 2, i + 3);
		}
		
		/* We finished the object */
		object->end();
		
		/* Convert triangle list to a mesh */
		object->convertToMesh(object_name);
	}
	catch (Ogre::Exception &e)
	{
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
	}
	catch(std::exception &e)
	{
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
	}
}

void MeshFactory::CreateConeGeometry(Ogre::String object_name, int num_circle_samples)
{
	try
	{
		/* Retrieve scene manager and root scene node */
		Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create the 3D object */
		Ogre::ManualObject* object = NULL;
		object = scene_manager->createManualObject(object_name);
		object->setDynamic(false);

		/* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta; // Angles for circle
		float cone_length = 1.0f;
		float cone_radius = 0.5f;
		Ogre::Vector3 circle_center_1 = Ogre::Vector3(0.0f, 0.5f * cone_length, 0.0f);
		Ogre::Vector3 circle_center_2 = Ogre::Vector3(0.0f, -0.5f * cone_length, 0.0f);
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);
		Ogre::Vector2 texture_coord;

		for (int i = 0; i < num_circle_samples; i++)
		{
			theta = Ogre::Math::TWO_PI * (((float)i + 0.5f) / (float)num_circle_samples); // circle sample (angle theta)
				
			/* Define position, normal and color of vertex */
			Ogre::Vector3 outerEdge = Ogre::Vector3(cos(theta), 0.0f, sin(theta)).normalisedCopy();
			vertex_normal = ((cone_length * outerEdge) + (cone_radius * Ogre::Vector3(0.0f, 1.0f, 0.0f))).normalisedCopy();
			vertex_position = circle_center_1;
			vertex_color = Ogre::ColourValue(1.0f, 0.0f, 0.0f);
			texture_coord = Ogre::Vector2(0.5f, 0.0f);

			object->position(circle_center_1);
			object->normal(circle_center_1);
			object->colour(vertex_color);
			object->textureCoord(texture_coord);
			
			vertex_position = circle_center_2 + outerEdge * cone_radius;
			vertex_color = Ogre::ColourValue(0.0f, 1.0f, 0.0f);
			texture_coord = Ogre::Vector2(((float)i)/((float)num_circle_samples), 1.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color);
			object->textureCoord(texture_coord);
			
			vertex_normal = circle_center_2;
			vertex_color = Ogre::ColourValue(0.0f, 0.0f, 1.0f);
			texture_coord = Ogre::Vector2(cos(theta) / 2.0f, sin(theta) / 2.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color);
			object->textureCoord(texture_coord);
		}
		
		vertex_color = Ogre::ColourValue(0.0f, 0.0f, 1.0f);
		texture_coord = Ogre::Vector2(0.5f, 0.5f);

		object->position(circle_center_2);
		object->normal(circle_center_2);
		object->colour(vertex_color);
		object->textureCoord(texture_coord);

		int c2 = num_circle_samples * 3;

		/* Add triangles to the object */
		for (int i = 0; i < num_circle_samples; i++)
		{
			int c1 = i * 3;
			int s11 = (i * 3) + 1;
			int s12 = (i * 3) + 2;
			int s21 = ((i * 3) + 4) % (num_circle_samples * 3);
			int s22 = ((i * 3) + 5) % (num_circle_samples * 3);

			object->triangle(c1, s21, s11);
			object->triangle(c2, s12, s22);
		}
		
		/* We finished the object */
		object->end();
		
		/* Convert triangle list to a mesh */
		object->convertToMesh(object_name);
	}
	catch (Ogre::Exception &e)
	{
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
	}
	catch(std::exception &e)
	{
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
	}
}

void MeshFactory::CreateCylinderGeometry(Ogre::String object_name, int num_circle_samples)
{
	try
	{
		/* Retrieve scene manager and root scene node */
		Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create the 3D object */
		Ogre::ManualObject* object = NULL;
		object = scene_manager->createManualObject(object_name);
		object->setDynamic(false);

		/* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta; // Angles for circle
		float cylinder_length = 1.0f;
		float cylinder_radius = 0.25f;
		Ogre::Vector3 circle_center_1 = Ogre::Vector3(0.0f, 0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 circle_center_2 = Ogre::Vector3(0.0f, -0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);
		Ogre::Vector2 texture_coord;

		for (int i = 0; i < num_circle_samples; i++)
		{
			theta = Ogre::Math::TWO_PI * (((float)i + 0.5f) / (float)num_circle_samples); // circle sample (angle theta)
				
			/* Define position, normal and color of vertex */
			vertex_normal = Ogre::Vector3(cos(theta), 0.0f, sin(theta));
			vertex_position = circle_center_1 + vertex_normal * cylinder_radius;
			texture_coord = Ogre::Vector2(((float)i)/((float)num_circle_samples), 0.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
			object->textureCoord(texture_coord);
			
			vertex_normal = circle_center_1;
			texture_coord = Ogre::Vector2(cos(theta) / 2.0f, sin(theta) / 2.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
			object->textureCoord(texture_coord);
				
			vertex_normal = Ogre::Vector3(cos(theta), 0.0f, sin(theta));
			vertex_position = circle_center_2 + vertex_normal * cylinder_radius;
			texture_coord = Ogre::Vector2(((float)i)/((float)num_circle_samples), 1.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
			object->textureCoord(texture_coord);
			
			vertex_normal = circle_center_2;
			texture_coord = Ogre::Vector2(cos(theta) / 2.0f, sin(theta) / 2.0f);

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
			object->textureCoord(texture_coord);
		}

		vertex_normal = Ogre::Vector3(0.0f, 0.0f, 0.0f);
		texture_coord = Ogre::Vector2(0.5f, 0.5f);

		object->position(circle_center_1);
		object->normal(circle_center_1);
		object->colour(vertex_color);
		object->textureCoord(texture_coord);

		object->position(circle_center_2);
		object->normal(circle_center_2);
		object->colour(vertex_color);
		object->textureCoord(texture_coord);

		int c1 = num_circle_samples * 4;
		int c2 = (num_circle_samples * 4) + 1;

		/* Add triangles to the object */
		for (int i = 0; i < num_circle_samples; i++)
		{
			int s11 = i * 4;
			int s12 = i * 4 + 1;
			int s21 = (i * 4) + 2;
			int s22 = (i * 4) + 3;
			int s31 = ((i * 4) + 4) % (num_circle_samples * 4);
			int s32 = ((i * 4) + 5) % (num_circle_samples * 4);
			int s41 = ((i * 4) + 6) % (num_circle_samples * 4);
			int s42 = ((i * 4) + 7) % (num_circle_samples * 4);

			object->triangle(c1, s32, s12);
			object->triangle(c2, s22, s42);
			object->triangle(s11, s31, s21);
			object->triangle(s21, s31, s41);
		}
		
		/* We finished the object */
		object->end();
		
		/* Convert triangle list to a mesh */
		object->convertToMesh(object_name);
	}
	catch (Ogre::Exception &e)
	{
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
	}
	catch(std::exception &e)
	{
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
	}
}

void MeshFactory::CreateTorusGeometry(Ogre::String object_name, float loop_radius, float circle_radius, int num_loop_samples, int num_circle_samples)
{
    try {
		/* Create a torus and add it to the resource list
		   The torus is built from a large loop with small circles around the loop */

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta, phi; // Angles for circles
		Ogre::Vector3 loop_center;
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);
		Ogre::Vector2 texture_coord;
				
		for (int i = 0; i < num_loop_samples; i++){ // large loop
			
			theta = Ogre::Math::TWO_PI*i/num_loop_samples; // loop sample (angle theta)
			loop_center = Ogre::Vector3(loop_radius*cos(theta), loop_radius*sin(theta), 0); // centre of a small circle

			for (int j = 0; j < num_circle_samples; j++){ // small circle
				
				phi = Ogre::Math::TWO_PI*j/num_circle_samples; // circle sample (angle phi)
				
				/* Define position, normal and color of vertex */
				vertex_normal = Ogre::Vector3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
				vertex_position = loop_center + vertex_normal*circle_radius;
				/*Ogre::Vector3(loop_center.x + local_normal.x*circle_radius, 
				                loop_center.y + local_normal.y*circle_radius, 
				     			loop_center.z + local_normal.z*circle_radius);*/
				texture_coord = Ogre::Vector2(((float)i)/((float)num_loop_samples), 1.0f-((float)j)/((float)num_circle_samples));

				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
				object->textureCoord(texture_coord);
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < num_loop_samples; i++){
			for (int j = 0; j < num_circle_samples; j++){
				// Two triangles per quad
				object->triangle(((i + 1) % num_loop_samples)*num_circle_samples + j, 
							     i*num_circle_samples + ((j + 1) % num_circle_samples),
								 i*num_circle_samples + j);
				object->triangle(((i + 1) % num_loop_samples)*num_circle_samples + j,
					             ((i + 1) % num_loop_samples)*num_circle_samples + ((j + 1) % num_circle_samples),
								 i*num_circle_samples + ((j + 1) % num_circle_samples));
			}
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void MeshFactory::CreateSphereGeometry(Ogre::String object_name, int num_samples_theta, int num_samples_phi)
{
    try {
		/* Create a sphere */

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta, phi; // Angles for parametric equation
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color;
		Ogre::Vector2 texture_coord;
		
				
		for (int i = 0; i < num_samples_theta; i++){
			
			theta = Ogre::Math::TWO_PI*i/(num_samples_theta-1); // angle theta
			
			for (int j = 0; j < num_samples_phi; j++){
				
				phi = Ogre::Math::PI*j/(num_samples_phi-1); // angle phi
				
				/* Define position, normal and color of vertex */
				vertex_normal = Ogre::Vector3(cos(theta)*sin(phi), sin(theta)*sin(phi), -cos(phi));
				// We need z = -cos(phi) to make sure that the z coordinate runs from -1 to 1 as phi runs from 0 to pi
				// Otherwise, the normal will be inverted
				vertex_position = Ogre::Vector3(vertex_normal.x*0.5f, 
					                            vertex_normal.y*0.5f, 
												vertex_normal.z*0.5f),
				/*vertex_color = Ogre::ColourValue(1.0 - ((float) i / (float) num_samples_theta), 
				                                 (float) i / (float) num_samples_theta, 
				                                 (float) j / (float) num_samples_phi);*/
				vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0);
				texture_coord = Ogre::Vector2(((float)i)/((float)num_samples_theta), 1.0f-((float)j)/((float)num_samples_phi));
								
				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
				object->textureCoord(texture_coord);
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < num_samples_theta; i++){
			for (int j = 0; j < (num_samples_phi-1); j++){
				// Two triangles per quad
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									i*num_samples_phi + (j + 1),
									i*num_samples_phi + j);
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									((i + 1) % num_samples_theta)*num_samples_phi + (j + 1), 
									i*num_samples_phi + (j + 1));
			}
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void MeshFactory::CreateSemisphereGeometry(Ogre::String object_name, float portion, int num_samples_theta, int num_samples_phi)
{
    try {
		/* Create a sphere */

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta, phi; // Angles for parametric equation
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color;
		Ogre::Vector2 texture_coord;
		
				
		for (int i = 0; i < num_samples_theta; i++){
			
			theta = Ogre::Math::TWO_PI*i/(num_samples_theta-1); // angle theta
			
			for (int j = 0; j < num_samples_phi; j++){
				
				phi = (Ogre::Math::PI*portion)*j/(num_samples_phi-1) + (Ogre::Math::PI * (1 - portion)); // angle phi
				
				/* Define position, normal and color of vertex */
				vertex_normal = Ogre::Vector3(cos(theta)*sin(phi), sin(theta)*sin(phi), -cos(phi));
				// We need z = -cos(phi) to make sure that the z coordinate runs from -1 to 1 as phi runs from 0 to pi
				// Otherwise, the normal will be inverted
				vertex_position = Ogre::Vector3(vertex_normal.x*0.5f, 
					                            vertex_normal.y*0.5f, 
												vertex_normal.z*0.5f),
				/*vertex_color = Ogre::ColourValue(1.0 - ((float) i / (float) num_samples_theta), 
				                                 (float) i / (float) num_samples_theta, 
				                                 (float) j / (float) num_samples_phi);*/
				vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0);
				texture_coord = Ogre::Vector2(((float)i)/((float)num_samples_theta), 1.0f-((float)j)/((float)num_samples_phi));
								
				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
				object->textureCoord(texture_coord);
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < (num_samples_theta); i++){
			for (int j = 0; j < (num_samples_phi-1); j++){
				// Two triangles per quad
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									i*num_samples_phi + (j + 1),
									i*num_samples_phi + j);
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									((i + 1) % num_samples_theta)*num_samples_phi + (j + 1), 
									i*num_samples_phi + (j + 1));
			}
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void MeshFactory::CreateUnculledSemisphereGeometry(Ogre::String object_name, float portion, int num_samples_theta, int num_samples_phi)
{
    try {
		/* Create a sphere */

        /* Retrieve scene manager and root scene node */
        Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
        Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

        /* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create triangle list for the object */
		object->begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta, phi; // Angles for parametric equation
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color;
		Ogre::Vector2 texture_coord;
		
				
		for (int i = 0; i < num_samples_theta; i++){
			
			theta = Ogre::Math::TWO_PI*i/(num_samples_theta-1); // angle theta
			
			for (int j = 0; j < num_samples_phi; j++){
				
				phi = (Ogre::Math::PI*portion)*j/(num_samples_phi-1) + (Ogre::Math::PI * (1 - portion)); // angle phi
				
				/* Define position, normal and color of vertex */
				vertex_normal = Ogre::Vector3(cos(theta)*sin(phi), sin(theta)*sin(phi), -cos(phi));
				// We need z = -cos(phi) to make sure that the z coordinate runs from -1 to 1 as phi runs from 0 to pi
				// Otherwise, the normal will be inverted
				vertex_position = Ogre::Vector3(vertex_normal.x*0.5f, 
					                            vertex_normal.y*0.5f, 
												vertex_normal.z*0.5f),
				/*vertex_color = Ogre::ColourValue(1.0 - ((float) i / (float) num_samples_theta), 
				                                 (float) i / (float) num_samples_theta, 
				                                 (float) j / (float) num_samples_phi);*/
				vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0);
				texture_coord = Ogre::Vector2(((float)i)/((float)num_samples_theta), 1.0f-((float)j)/((float)num_samples_phi));
								
				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
				object->textureCoord(texture_coord);
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < num_samples_theta; i++){
			for (int j = 0; j < (num_samples_phi-1); j++){
				// Two triangles per quad
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									i*num_samples_phi + (j + 1),
									i*num_samples_phi + j);
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + j, 
									((i + 1) % num_samples_theta)*num_samples_phi + (j + 1), 
									i*num_samples_phi + (j + 1));
			}
		}
		for (int i = 0; i < num_samples_theta; i++){
			for (int j = 0; j < (num_samples_phi-1); j++){
				// Two triangles per quad
				object->triangle(i*num_samples_phi + (j + 1),
									((i + 1) % num_samples_theta)*num_samples_phi + j,
									i*num_samples_phi + j);
				object->triangle(((i + 1) % num_samples_theta)*num_samples_phi + (j + 1),
									((i + 1) % num_samples_theta)*num_samples_phi + j,
									i*num_samples_phi + (j + 1));
			}
		}
		
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        object->convertToMesh(object_name);
    }
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}

void MeshFactory::CreateIcosahedron(Ogre::String object_name)
{
	try {
		/* Retrieve scene manager and root scene node */
		Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create the 3D object */
        Ogre::ManualObject* object = NULL;
        Ogre::String object_name = "Icosahedron";
        object = scene_manager->createManualObject(object_name);
        object->setDynamic(false);

        /* Create triangle list for the object */
		Ogre::String material_name = "ObjectMaterial";
        object->begin(material_name, Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Vertices of an icosahedron */
		Ogre::Vector2 v = Ogre::Vector2(0.525731112119133606f, 0.850650808352039932f).normalisedCopy();
		float X = v.x / 2.0f;
		float Z = v.y / 2.0f;
        float vdata[12][3] = {
	        {-X, 0.0f, Z}, {X, 0.0f, Z}, {-X, 0.0f, -Z}, {X, 0.0f, -Z},
	        {0.0f, Z, X}, {0.0f, Z, -X}, {0.0f, -Z, X}, {0.0f, -Z, -X},
	        {Z, X, 0.0f}, {-Z, X, 0.0f}, {Z, -X, 0.0f}, {-Z, -X, 0.0f}};
 
		/* Vertex colors */
		float clr[12][3] = {
			{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f},
			{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.6f, 0.4f, 0.2f},
			{1.0f, 0.2f, 0.8f}, {1.0f, 0.4f, 0.0f}, {0.0f, 0.6f, 0.0f}, {0.6f, 0.6f, 0.6f}};

        /* Faces */
        int tindices [20][3] = {
	        {1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4},	{1, 8, 4}, 
	        {1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2}, 
	        {3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11},	{6, 1, 0}, 
	        {10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7}, 
        };
		
		/* Add vertices and faces */
		for (int i = 0; i < 12; i++){
			object->position(Ogre::Vector3(vdata[i][0], vdata[i][1], vdata[i][2]));
			object->normal(Ogre::Vector3(vdata[i][0], vdata[i][1], vdata[i][2]));
			object->colour(Ogre::ColourValue(clr[i][0], clr[i][1], clr[i][2]));
		}

		for (int i = 0; i < 20; i++){
			object->triangle(tindices[i][0], tindices[i][1], tindices[i][2]);
		}
   
		/* We finished the object */
        object->end();
		
        /* Convert triangle list to a mesh */
        Ogre::String mesh_name = "Icosahedron";
        object->convertToMesh(mesh_name);

	}
    catch (Ogre::Exception &e){
        throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
    }
    catch(std::exception &e){
        throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
    }
}