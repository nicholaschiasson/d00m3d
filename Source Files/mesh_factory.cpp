#include "mesh_factory.h"

std::auto_ptr<Ogre::Root> *MeshFactory::ogre_root_ = 0;

void MeshFactory::Init(std::auto_ptr<Ogre::Root> *root)
{
	ogre_root_ = root;
}

void MeshFactory::CreateCylinder(Ogre::String object_name, Ogre::String material_name, Ogre::ColourValue color, float cylinder_length, float circle_radius, int num_circle_samples)
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
		object->begin(material_name, Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta; // Angles for circle
		Ogre::Vector3 circle_center_1 = Ogre::Vector3(0.0, 0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 circle_center_2 = Ogre::Vector3(0.0, -0.5f * cylinder_length, 0.0f);
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color = color;
		bool default_color = (color == Ogre::ColourValue(-1.0f, -1.0f, -1.0f));

		for (int i = 0; i < num_circle_samples; i++)
		{
			theta = Ogre::Math::TWO_PI*i/num_circle_samples; // circle sample (angle theta)
				
			/* Define position, normal and color of vertex */
			vertex_normal = Ogre::Vector3(cos(theta), 0.0f, sin(theta));
			vertex_position = circle_center_1 + vertex_normal * circle_radius;
			if (default_color)
			{
				vertex_color = Ogre::ColourValue(1.0f - ((float) i / (float) num_circle_samples), 
													(float) i / (float) num_circle_samples, 
													(float) i / (float) num_circle_samples);
			}

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
				
			vertex_position = circle_center_2 + vertex_normal * circle_radius;

			object->position(vertex_position);
			object->normal(vertex_normal);
			object->colour(vertex_color); 
		}

		vertex_normal = Ogre::Vector3(0.0f, 0.0f, 0.0f);
		if (default_color)
		{
			vertex_color = Ogre::ColourValue();
		}

		object->position(circle_center_1);
		object->normal(vertex_normal);
		object->colour(vertex_color);

		object->position(circle_center_2);
		object->normal(vertex_normal);
		object->colour(vertex_color);

		int c1 = num_circle_samples * 2;
		int c2 = (num_circle_samples * 2) + 1;

		/* Add triangles to the object */
		for (int i = 0; i < num_circle_samples; i++)
		{
			int s1 = i * 2;
			int s2 = (i * 2) + 1;
			int s3 = ((i * 2) + 2) % (num_circle_samples * 2);
			int s4 = ((i * 2) + 3) % (num_circle_samples * 2);

			object->triangle(c1, s3, s1);
			object->triangle(c2, s2, s4);
			object->triangle(s1, s3, s2);
			object->triangle(s2, s3, s4);
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

void MeshFactory::CreateTorus(Ogre::String object_name, Ogre::String material_name, float loop_radius, float circle_radius, int num_loop_samples, int num_circle_samples)
{
	try
	{
		/* Create a torus
			The torus is built from a large loop with small circles around the loop */

		/* Retrieve scene manager and root scene node */
		Ogre::SceneManager* scene_manager = (*ogre_root_)->getSceneManager("MySceneManager");
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

		/* Create the 3D object */
		Ogre::ManualObject* object = NULL;
		object = scene_manager->createManualObject(object_name);
		object->setDynamic(false);

		/* Create triangle list for the object */
		object->begin(material_name, Ogre::RenderOperation::OT_TRIANGLE_LIST);

		/* Add vertices to the object */
		float theta, phi; // Angles for circles
		Ogre::Vector3 loop_center;
		Ogre::Vector3 vertex_position;
		Ogre::Vector3 vertex_normal;
		Ogre::ColourValue vertex_color;
				
		for (int i = 0; i < num_loop_samples; i++)
		{
			// large loop
			theta = Ogre::Math::TWO_PI*i/num_loop_samples; // loop sample (angle theta)
			loop_center = Ogre::Vector3(loop_radius*cos(theta), loop_radius*sin(theta), 0); // centre of a small circle

			for (int j = 0; j < num_circle_samples; j++)
			{
				// small circle
				phi = Ogre::Math::TWO_PI*j/num_circle_samples; // circle sample (angle phi)
				
				/* Define position, normal and color of vertex */
				vertex_normal = Ogre::Vector3(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));
				vertex_position = loop_center + vertex_normal*circle_radius;
				/*Ogre::Vector3(loop_center.x + local_normal.x*circle_radius, 
								loop_center.y + local_normal.y*circle_radius, 
				     			loop_center.z + local_normal.z*circle_radius);*/
				vertex_color = Ogre::ColourValue(1.0f - ((float) i / (float) num_loop_samples), 
													(float) i / (float) num_loop_samples, 
													(float) j / (float) num_circle_samples);
				/*vertex_color = Ogre::ColourValue(0.0, 0.0, 1.0);*/

				/* Add them to the object */
				object->position(vertex_position);
				object->normal(vertex_normal);
				object->colour(vertex_color); 
			}
		}

		/* Add triangles to the object */
		for (int i = 0; i < num_loop_samples; i++)
		{
			for (int j = 0; j < num_circle_samples; j++)
			{
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
	catch (Ogre::Exception &e)
	{
		throw(OgreAppException(std::string("Ogre::Exception: ") + std::string(e.what())));
	}
	catch(std::exception &e)
	{
		throw(OgreAppException(std::string("std::Exception: ") + std::string(e.what())));
	}
}