#ifndef BLACK_HOLE_PROJECTILE_H
#define BLACK_HOLE_PROJECTILE_H

#include "black_hole.h"

class BlackHoleProjectile : public BlackHole
{
public:
	enum BLACK_HOLE_PROJECTILE_STATE
	{
		STATE_AIRBORN,
		STATE_EXPANDING,
		STATE_OBLITERATING,
		STATE_DYING,
	};

	BlackHoleProjectile();
	BlackHoleProjectile(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual ~BlackHoleProjectile();
    virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void Damage(float damage);

protected:
	BLACK_HOLE_PROJECTILE_STATE state;
	float timer;

};

#endif // BLACK_HOLE_PROJECTILE_H
