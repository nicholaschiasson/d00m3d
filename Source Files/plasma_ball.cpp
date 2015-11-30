#include "plasma_ball.h"

PlasmaBall::PlasmaBall(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, float dmg, unsigned int parentID) :
	ParticleEffect(sceneManager, parentNode, "plasmaSplineControlPoints", "SplineParticleMaterial", physicsEngine, 6.0f), damage(dmg)
{
	mass = 10.0f;
	dynamic = true;
	bodyType = ENTITY_BODY_SPHERE;
}

PlasmaBall::~PlasmaBall()
{
}

void PlasmaBall::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->Damage(damage);
	alive = false;
}

float PlasmaBall::getDamage()
{
	return damage;
}