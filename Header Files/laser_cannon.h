#ifndef LASER_CANNON_H
#define LASER_CANNON_H

#include "weapon.h"
#include "laser.h"

class LaserCannon: public Weapon
{
public:
	LaserCannon();
	~LaserCannon();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);

	void fire();

private:
	int duration;
	Laser laser;
};

#endif // LASER_CANNON_H