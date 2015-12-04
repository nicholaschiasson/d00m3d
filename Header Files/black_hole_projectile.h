#ifndef BLACK_HOLE_PROJECTILE_H
#define BLACK_HOLE_PROJECTILE_H

#include "physics_entity.h"
#include "input_manager.h"

class BlackHoleProjectile : public PhysicsEntity
{
public:
	BlackHoleProjectile();
	virtual ~BlackHoleProjectile();
    virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void Damage(float damage);

private:
	float gravitationalPull;
};

#endif // BLACK_HOLE_PROJECTILE_H
