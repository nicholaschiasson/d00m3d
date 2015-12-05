#ifndef LASER_CANNON_H
#define LASER_CANNON_H

#include "weapon.h"
#include "laser.h"

class LaserCannon: public Weapon
{
public:
	LaserCannon();
	~LaserCannon();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::SceneNode *world, PhysicsEngine &physicsEngine, ParticleEngine *particleEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe, Ogre::Vector3 velocity);
	
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void detachFrom(PhysicsEngine &physicsEngine);

	virtual PhysicsEntity *fire();
	virtual void upgrade(int maxCooldown, int dmg);

	virtual void setVisible(bool visible, bool cascade = true);

private:
	int duration;
	Laser laser;
};

#endif // LASER_CANNON_H