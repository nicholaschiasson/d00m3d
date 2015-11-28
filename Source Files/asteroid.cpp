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
	float radius = Ogre::Math::RangeRandom(100.0f, 150.0f);
	scale(radius, radius, radius);
	sceneNode->attachObject(asteroidEntity);
}

void Asteroid::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{

}
