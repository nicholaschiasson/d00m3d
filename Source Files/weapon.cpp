#include "weapon.h"

Weapon::Weapon() : timer(0), cooldown(5), myState(WEAPON_READY), damage(250)
{
}

Weapon::~Weapon()
{
}

void Weapon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	
	//setting our mass to 0
	bodyType = ENTITY_BODY_METAPHYSICAL;
	dynamic = false;
	mass = 0.0f;
}

void Weapon::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{

}

void Weapon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
	damage = dmg;
}

int Weapon::getCooldown() const
{
	return cooldown;
}

int Weapon::getDamage() const
{
	return damage;
}

Weapon::WEAPON_STATE Weapon::getState()
{
	return myState;
}