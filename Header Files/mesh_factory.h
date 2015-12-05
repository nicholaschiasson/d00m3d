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
	static void CreateCubeGeometry(Ogre::String object_name = "Cube");
	static void CreateConeGeometry(Ogre::String object_name = "Cone", int num_circle_samples = 64);
	static void CreateCylinderGeometry(Ogre::String object_name = "Cylinder", int num_circle_samples = 64);
	static void CreateTorusGeometry(Ogre::String object_name = "Torus", float loop_radius = 0.375f, float circle_radius = 0.125f,
		int num_loop_samples = 128, int num_circle_samples = 64);
	static void CreateSphereGeometry(Ogre::String object_name = "Sphere", int num_samples_theta = 64, int num_samples_phi = 32);
	static void CreateSemisphereGeometry(Ogre::String object_name = "Semisphere", float portion = 0.5f, int num_samples_theta = 64, int num_samples_phi = 16);
	static void CreateUnculledSemisphereGeometry(Ogre::String object_name = "UnculledSemisphere", float portion = 0.5f, int num_samples_theta = 64, int num_samples_phi = 16);
	static void CreateIcosahedron(Ogre::String object_name = "Icosahedron");

private:
	static std::auto_ptr<Ogre::Root> *ogre_root_;
};

#endif // MESH_FACTORY_H