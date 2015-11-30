#ifndef PLASMA_CANNON_H
#define PLASMA_CANNON_H

#include "weapon.h"
#include <OgreEntity.h>

class PlasmaCannon: public Weapon
{
public:
	PlasmaCannon();
	~PlasmaCannon();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void detachFrom(PhysicsEngine &physicsEngine);

	void fire();
	virtual void upgrade(int maxCooldown, int dmg);

private:

};

#endif // PLASMA_CANNON_H