#include "mesh_factory.h"

std::auto_ptr<Ogre::Root> *MeshFactory::ogre_root_ = 0;

void MeshFactory::Initialize(std::auto_ptr<Ogre::Root> *root)
{
	ogre_root_ = root;
	CreateCubeGeometry("Cube");
	CreateCylinderGeometry("Cylinder");
	CreateTorusGeometry("Torus");
	CreateSphereGeometry("Sphere");
}

void MeshFactory::CreateCubeGeometry(Ogre::String object_name, float width, float height, float depth)
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
		float widthBy2 = width / 2.0f;
		float heightBy2 = height / 2.0f;
		float depthBy2 = depth / 2.0f;
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

void MeshFactory::CreateCylinderGeometry(Ogre::String object_name, float cylinder_length, float circle_radius, int num_circle_samples)
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
		Ogre::Vector3 circle_center_1 = Ogre::Vector3(0.0, 0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 circle_center_2 = Ogre::Vector3(0.0, -0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color = Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f);
		Ogre::Vector2 texture_coord;

		for (int i = 0; i < num_circle_samples; i++)
		{
			theta = Ogre::Math::TWO_PI*i/num_circle_samples; // circle sample (angle theta)
				
			/* Define position, normal and color of vertex */
			vertex_normal = Ogre::Vector3(cos(theta), 0.0f, sin(theta));
			vertex_position = circle_center_1 + vertex_normal * circle_radius;
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
			vertex_position = circle_center_2 + vertex_normal * circle_radius;
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

void MeshFactory::CreateSphereGeometry(Ogre::String object_name, float radius, int num_samples_theta, int num_samples_phi){

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
				vertex_position = Ogre::Vector3(vertex_normal.x*radius, 
					                            vertex_normal.y*radius, 
												vertex_normal.z*radius),
				/*vertex_color = Ogre::ColourValue(1.0 - ((float) i / (float) num_samples_theta), 
				                                 (float) i / (float) num_samples_theta, 
				                                 (float) j / (float) num_samples_phi);*/
				vertex_color = Ogre::ColourValue(0.0, 0.0, 0.0);
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