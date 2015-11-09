#include "asteroid.h"

#include "OgreEntity.h"

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *worldNode){


}

void Asteroid::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode *worldNode, std::string object_name)
{
	Ogre::Entity *asteroidEntity = sceneManager->createEntity("Icosahedron");
	asteroidEntity->setMaterialName("AsteroidMaterial");
	sceneNode = worldNode->createChildSceneNode(object_name);
	name = object_name;
	sceneNode->attachObject(asteroidEntity);
}

Ogre::SceneNode* Asteroid::getAsteroidSceneNode(){

	return sceneNode;
}