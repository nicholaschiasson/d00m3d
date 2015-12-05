#include "black_hole_projectile.h"

#include "OgreEntity.h"

BlackHoleProjectile::BlackHoleProjectile() : state(STATE_AIRBORN), timer(0.0f)
{
}

BlackHoleProjectile::BlackHoleProjectile(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID) :
	state(STATE_AIRBORN), timer(0.0f)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}

BlackHoleProjectile::~BlackHoleProjectile()
{
}

void BlackHoleProjectile::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	BlackHole::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	bodyType = ENTITY_BODY_METAPHYSICAL_SPHERE;
	dynamic = true;
	gravitational = true;
	mass = 10.0f;

	setScale(1.0f, 1.0f, 1.0f);
}

void BlackHoleProjectile::Update(const Ogre::FrameEvent &fe)
{
	BlackHole::Update(fe);
	 
	switch (state)
	{
	case STATE_AIRBORN:
		if (timer >= 5.0f)
		{
			state = STATE_EXPANDING;
			dynamic = false;
		}
		break;
	case STATE_EXPANDING:
		if (GetRadius() < 100.0f)
			scale(1.0f + 10.0f * fe.timeSinceLastFrame, 1.0f + 10.0f * fe.timeSinceLastFrame, 1.0f + 10.0f * fe.timeSinceLastFrame);
		if (timer >= 6.0f)
		{
			mass = 1000000000000000.0f;
			state = STATE_OBLITERATING;
		}
		break;
	case STATE_OBLITERATING:
		if (timer >= 11.0f)
		{
			mass = 10.0f;
			state = STATE_DYING;
		}
		break;
	case STATE_DYING:
		scale(1.0f - 10.0f * fe.timeSinceLastFrame, 1.0f - 10.0f * fe.timeSinceLastFrame, 1.0f - 10.0f * fe.timeSinceLastFrame);
		if (timer >= 12.0f)
		{
			alive = false;
		}
		break;
	default:
		break;
	}
	timer += fe.timeSinceLastFrame;
}

void BlackHoleProjectile::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->spaghettify();
}

void BlackHoleProjectile::Damage(float damage)
{
	// nope
}