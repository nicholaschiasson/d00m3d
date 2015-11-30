#ifndef PLASMA_BALL_H
#define PLASMA_BALL_H

#include "particle_effect.h"

class PlasmaBall : public ParticleEffect
{
public:
	PlasmaBall(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, float dmg = 500.0f, unsigned int parentID = -1);
	~PlasmaBall();

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);

	virtual float getDamage();

private:
	float damage;

};

#endif // PLASMA_BALL_H