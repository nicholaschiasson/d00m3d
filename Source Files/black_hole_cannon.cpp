#include "black_hole_cannon.h"

BlackHoleCannon::BlackHoleCannon()
{
	materialPrefix = "BlackHole";
	cooldown = 30;
	energyRequirement = 90.0f;
}

BlackHoleCannon::~BlackHoleCannon()
{
}

void BlackHoleCannon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::SceneNode *world, PhysicsEngine &physicsEngine, ParticleEngine *particleEngine, unsigned int parentID)
{
	Weapon::Initialize(sceneManager, parentNode, world, physicsEngine, particleEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);
}

void BlackHoleCannon::Update(const Ogre::FrameEvent &fe, Ogre::Vector3 v)
{
	Weapon::Update(fe, v);
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

PhysicsEntity *BlackHoleCannon::fire()
{
	if(myState == WEAPON_READY){
		myState = WEAPON_COOLDOWN;
		timer = cooldown;
		unsigned int pid = (parentObjectID == -1 ? objectID : parentObjectID);
		BlackHoleProjectile *blackHole = new BlackHoleProjectile(sceneManager, worldNode, *physicsEngine, pid);
		blackHole->translate(barrel->_getDerivedPosition() + barrel->_getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z);
		blackHole->setOrientation(barrel->_getDerivedOrientation());
		blackHole->SetVelocity(relativeVelocity);
		blackHole->ApplyForce(blackHole->getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z * 1000.0f);
		return blackHole;
	}
	return 0; // return a black hole
}

void BlackHoleCannon::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
}