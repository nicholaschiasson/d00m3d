#include "asteroid.h"
#include "OgreEntity.h"

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	mass = 5000.0f;

	Ogre::Entity *asteroidEntity = sceneManager->createEntity("Icosahedron");
	asteroidEntity->setMaterialName("AsteroidMaterial");
	sceneNode->attachObject(asteroidEntity);
}