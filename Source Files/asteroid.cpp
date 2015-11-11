#include "asteroid.h"
#include "OgreEntity.h"

Asteroid::Asteroid()
{
}

Asteroid::Asteroid(Ogre::SceneManager *sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
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
	Ogre::String s = "Asteroid" + Ogre::StringConverter::toString(entityCount);
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Asteroid" + Ogre::StringConverter::toString(entityCount));
	scale(3.0f, 3.0f, 3.0f);
	sceneNode->attachObject(asteroidEntity);
}

void Asteroid::Collide(PhysicsEntity *physicsEntity)
{

}
