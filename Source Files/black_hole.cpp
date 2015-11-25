#include "black_hole.h"

#include "OgreEntity.h"

BlackHole::BlackHole()
{
}

BlackHole::~BlackHole()
{
}

void BlackHole::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	bodyType = ENTITY_BODY_METAPHYSICAL_SPHERE;
	dynamic = false;
	gravitational = true;
	mass = 99999999999.0f;

	Ogre::Entity *bhEntity = sceneManager->createEntity("Sphere");
	Ogre::SceneNode *rootSceneNode = sceneManager->getRootSceneNode();
	bhEntity->setMaterialName("BlackHoleMaterial");
	sceneNode->attachObject(bhEntity);
	size = 100.0f;
	sceneNode->setScale(size,size,size);
}

void BlackHole::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->spaghettify();
}

void BlackHole::Damage(float damage)
{
	// nope
}

Ogre::SceneNode* BlackHole::getSceneNode(){

	return sceneNode;
}

float BlackHole::getSize(){
	return size;
}