#include "black_hole_cannon.h"

BlackHoleCannon::BlackHoleCannon()
{
	materialPrefix = "BlackHole";
}

BlackHoleCannon::~BlackHoleCannon()
{
}

void BlackHoleCannon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Weapon::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);
}

void BlackHoleCannon::Update(const Ogre::FrameEvent &fe)
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

void BlackHoleCannon::cleanup(PhysicsEngine &physicsEngine)
{
	Weapon::cleanup(physicsEngine);
}

void BlackHoleCannon::detachFrom(PhysicsEngine &physicsEngine)
{
	Weapon::detachFrom(physicsEngine);
}

void BlackHoleCannon::fire()
{
	if(myState == WEAPON_READY){
		myState = WEAPON_FIRING;
	}
}

void BlackHoleCannon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
}