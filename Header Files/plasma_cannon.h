#ifndef PLASMA_CANNON_H
#define PLASMA_CANNON_H

#include "weapon.h"
#include "plasma_ball.h"
#include <OgreEntity.h>

class PlasmaCannon: public Weapon
{
public:
	PlasmaCannon();
	~PlasmaCannon();

	virtual void Update(const Ogre::FrameEvent &fe, Ogre::Vector3 velocity);
	
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void detachFrom(PhysicsEngine &physicsEngine);

	virtual PhysicsEntity *fire();
	virtual void upgrade(int maxCooldown, int dmg);

	virtual float getDamage();

private:
	float damage;

};

#endif // PLASMA_CANNON_H