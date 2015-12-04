#include "black_hole_projectile.h"

#include "OgreEntity.h"

BlackHoleProjectile::BlackHoleProjectile()
{
}

BlackHoleProjectile::~BlackHoleProjectile()
{
}

void BlackHoleProjectile::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
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
	sceneNode->setScale(100.0f,100.0f,100.0f);
}

void BlackHoleProjectile::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->spaghettify();
}

void BlackHoleProjectile::Damage(float damage)
{
	// nope
}