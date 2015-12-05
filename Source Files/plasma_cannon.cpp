#include "plasma_cannon.h"

PlasmaCannon::PlasmaCannon() : damage(50.0f)
{
	materialPrefix = "Plasma";
	cooldown = 5;
	energyRequirement = 0.1f;
}

PlasmaCannon::~PlasmaCannon()
{
}

void PlasmaCannon::Update(const Ogre::FrameEvent &fe, Ogre::Vector3 v)
{
	Weapon::Update(fe, v);
	if(alive){
		if(timer == 0){
			switch(myState){
			case WEAPON_COOLDOWN:
				myState = WEAPON_READY;
				break;
			}
		}
		else{
			timer--;
		}
	}
}

void PlasmaCannon::cleanup(PhysicsEngine &physicsEngine)
{
	Weapon::cleanup(physicsEngine);
}

void PlasmaCannon::detachFrom(PhysicsEngine &physicsEngine)
{
	Weapon::detachFrom(physicsEngine);
}

PhysicsEntity *PlasmaCannon::fire()
{
	if(myState == WEAPON_READY){
		if (particleEngine != 0)
		{
			myState = WEAPON_COOLDOWN;
			timer = cooldown;
			unsigned int pid = (parentObjectID == -1 ? objectID : parentObjectID);
			PlasmaBall *plasma = new PlasmaBall(sceneManager, worldNode, *physicsEngine, damage, pid);
			plasma->setScale(1.0f, 1.0f, 1.0f);
			plasma->scale(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
			plasma->translate(barrel->_getDerivedPosition() + barrel->_getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z);
			plasma->setOrientation(barrel->_getDerivedOrientation());
			plasma->SetVelocity(relativeVelocity);
			plasma->ApplyForce(plasma->getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z * 1000.0f);
			particleEngine->addParticleEffect(plasma);
		}
	}
	return 0; // we don't actually return this one since luke's particle engine has its own update loop for particle effects
}

void PlasmaCannon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
	damage = (float)dmg;
}

float PlasmaCannon::getDamage()
{
	return damage;
}