#include "asteroid.h"

#include "OgreEntity.h"

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine);

	Ogre::Entity *asteroidEntity = sceneManager->createEntity("Icosahedron");
	asteroidEntity->setMaterialName("AsteroidMaterial");
	Ogre::String s = "Asteroid" + Ogre::StringConverter::toString(entityCount);
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Asteroid" + Ogre::StringConverter::toString(entityCount));
	name = asteroidNode->getName();
	sceneNode->attachObject(asteroidEntity);
}

Ogre::SceneNode* Asteroid::getAsteroidSceneNode(){

	return sceneNode;
}