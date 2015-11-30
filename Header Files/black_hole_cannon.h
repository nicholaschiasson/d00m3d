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

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::SceneNode *world, PhysicsEngine &physicsEngine, ParticleEngine *particleEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe, Ogre::Vector3 velocity);
	
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void detachFrom(PhysicsEngine &physicsEngine);

	virtual PhysicsEntity *fire();
	virtual void upgrade(int maxCooldown, int dmg);

private:

};

#endif // BLACK_HOLE_CANNON_H