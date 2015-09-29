#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <string>

#include "ogre_app_exception.h"

#include <OgreString.h>
#include <OgreColourValue.h>
#include <OgreRoot.h>
#include <OgreManualObject.h>

class MeshFactory
{
public:
	static void Init(std::auto_ptr<Ogre::Root> *root);
	static void CreateCylinder(Ogre::String object_name, Ogre::String material_name,
		Ogre::ColourValue color = Ogre::ColourValue(-1.0f, -1.0f, -1.0f), float cylinder_length = 1.0f,
		float circle_radius = 0.2f, int num_circle_samples = 30);
	static void CreateTorus(Ogre::String object_name, Ogre::String material_name, float loop_radius = 0.6,
		float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30);
private:
	static std::auto_ptr<Ogre::Root> *ogre_root_;
};

#endif // MESH_FACTORY_H