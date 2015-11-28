#include "laser.h"

Laser::Laser(): damage(250)
{
	//lalala
}

Laser::~Laser()
{
}

void Laser::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	//setting our mass to 0
	bodyType = ENTITY_BODY_METAPHYSICAL;
	dynamic = false;
	mass = 0.0f;

	Ogre::Entity *laserEntity = sceneManager->createEntity("Cylinder");
	laserEntity->setMaterialName("LaserMaterial");
	Ogre::SceneNode *laserSceneNode = sceneNode->createChildSceneNode("Laser" + Ogre::StringConverter::toString(entityCount));
	laserSceneNode->attachObject(laserEntity);
	laserSceneNode->scale(0.3f, 100.0f, 0.3f);
	laserSceneNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	laserSceneNode->translate(0,0,-50.5f);

	sceneNode->setVisible(false);
}

void Laser::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->Damage(damage * fe.timeSinceLastFrame);
}

void Laser::upgrade(int dmg)
{
	damage = dmg;
}

void Laser::fire()
{
	bodyType = ENTITY_BODY_METAPHYSICAL_RAY;
	sceneNode->setVisible(true);
}

void Laser::cooldown()
{
	bodyType = ENTITY_BODY_METAPHYSICAL;
	sceneNode->setVisible(false);
}

int Laser::getDamage() const
{
	return damage;
}