#include "laser_cannon.h"

LaserCannon::LaserCannon(): duration(5)
{
	materialPrefix = "Laser";
}

LaserCannon::~LaserCannon()
{
}

void LaserCannon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Weapon::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);

	laser.Initialize(sceneManager, barrel, physicsEngine, pid);
	laser.scale(1.0f / 0.25f, 1.0f / 0.25f, 1.0f / 1.5f);
	laser.translate(0.0f, 0.0f, 0.0f);
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

void LaserCannon::cleanup(PhysicsEngine &physicsEngine)
{
	laser.detachFrom(physicsEngine);
	Weapon::cleanup(physicsEngine);
}

void LaserCannon::detachFrom(PhysicsEngine &physicsEngine)
{
	laser.detachFrom(physicsEngine);
	Weapon::detachFrom(physicsEngine);
}

void LaserCannon::fire()
{
	if(myState == WEAPON_READY){
		myState = WEAPON_FIRING;
		timer = duration;
		laser.fire();
	}
}

void LaserCannon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
	laser.upgrade(dmg);
}