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
	static void Initialize(std::auto_ptr<Ogre::Root> *root);
	static void CreateIcosahedron(Ogre::String object_name);
	static void CreateCubeGeometry(Ogre::String object_name, float width = 1.0f, float height = 1.0f,
		float depth = 1.0f);
	static void CreateCylinderGeometry(Ogre::String object_name, float cylinder_length = 1.0f, 
		float circle_radius = 0.25f, int num_circle_samples = 64);
	static void CreateTorusGeometry(Ogre::String object_name, float loop_radius = 0.375f, float circle_radius = 0.125f,
		int num_loop_samples = 128, int num_circle_samples = 64);
	static void CreateSphereGeometry(Ogre::String object_name, float radius = 0.5, int num_samples_theta = 64,
		int num_samples_phi = 32);

private:
	static std::auto_ptr<Ogre::Root> *ogre_root_;
};

#endif // MESH_FACTORY_H