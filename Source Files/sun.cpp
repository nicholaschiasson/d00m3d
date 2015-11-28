#include "sun.h"

Sun::Sun(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}
Sun::Sun()
{
}
Sun::~Sun()
{
}
void Sun::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	mass = 100000.0f;

	Ogre::Entity *sunEntity = sceneManager->createEntity("Sphere");
	sunEntity->setMaterialName("SunMaterial");
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Sun" + Ogre::StringConverter::toString(entityCount));
	scale(500, 500, 500);
	sceneNode->attachObject(sunEntity);
}

void Sun::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
}