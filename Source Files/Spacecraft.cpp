#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft()
{
}

Spacecraft::~Spacecraft()
{
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager)
{
	Ogre::Entity *spacecraftEntity = sceneManager->createEntity("Sphere");
	Ogre::SceneNode *rootSceneNode = sceneManager->getRootSceneNode();
	spacecraftEntity->setMaterialName("ObjectMaterial");
	sceneNode = rootSceneNode->createChildSceneNode("testCube");
	sceneNode->attachObject(spacecraftEntity);
}