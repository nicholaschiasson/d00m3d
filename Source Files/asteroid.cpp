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

void Asteroid::Initialize(Ogre::SceneManager *sceneManager, std::string object_name)
{
	std::cout << "BEGINNING OF FILE" << std::endl;
	Ogre::Entity *asteroidEntity = sceneManager->createEntity("Icosahedron");
	Ogre::SceneNode *rootSceneNode = sceneManager->getRootSceneNode();
	asteroidEntity->setMaterialName("AsteroidMaterial");
	sceneNode = rootSceneNode->createChildSceneNode(object_name);
	name = object_name;
	sceneNode->attachObject(asteroidEntity);
}

Ogre::SceneNode* Asteroid::getAsteroidSceneNode(){

	return sceneNode;
}