#ifndef BLACK_HOLE_CANNON_H
#define BLACK_HOLE_CANNON_H

#include "weapon.h"
#include <OgreEntity.h>
#include "black_hole.h"

class BlackHoleCannon: public Weapon
{
public:
	BlackHoleCannon();
	~BlackHoleCannon();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void detachFrom(PhysicsEngine &physicsEngine);

	void fire();
	virtual void upgrade(int maxCooldown, int dmg);

private:

};

#endif // BLACK_HOLE_CANNON_H