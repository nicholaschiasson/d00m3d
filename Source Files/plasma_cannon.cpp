#include "plasma_cannon.h"

PlasmaCannon::PlasmaCannon()
{
	materialPrefix = "Plasma";
}

PlasmaCannon::~PlasmaCannon()
{
}

void PlasmaCannon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Weapon::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);
}

void PlasmaCannon::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);
	if(alive){
		if(timer == 0){
			switch(myState){
			case WEAPON_COOLDOWN:
				myState = WEAPON_READY;
				break;
			case WEAPON_FIRING:
				myState = WEAPON_COOLDOWN;
				timer = cooldown;
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

void PlasmaCannon::fire()
{
	if(myState == WEAPON_READY){
		myState = WEAPON_FIRING;
	}
}

void PlasmaCannon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
}