#include "laser_cannon.h"

LaserCannon::LaserCannon(): duration(5)
{
	//lalala
}

LaserCannon::~LaserCannon()
{
}

void LaserCannon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Weapon::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);

	laser.Initialize(sceneManager, sceneNode, physicsEngine, pid);
}

void LaserCannon::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);
	if(alive){
		if(timer == 0){
			switch(myState){
			case WEAPON_COOLDOWN:
				myState = WEAPON_READY;
				break;
			case WEAPON_FIRING:
				laser.cooldown();
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

void LaserCannon::fire()
{
	if(myState == WEAPON_READY){
		myState = WEAPON_FIRING;
		timer = duration;
		laser.fire();
	}
}