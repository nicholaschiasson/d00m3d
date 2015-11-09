#include "physics_entity.h"

PhysicsEntity::PhysicsEntity()
{
	appliedForce = 0.0f;
	mass = 1.0f;
}

PhysicsEntity::~PhysicsEntity()
{
}

void PhysicsEntity::Update(const Ogre::FrameEvent &fe)
{
	acceleration += appliedForce;
	appliedForce = 0;
}

void PhysicsEntity::ApplyForce(float x, float y, float z)
{
	if (dynamic)
	{
		appliedForce += Ogre::Vector3(x, y, z);
	}
}

void PhysicsEntity::ApplyForce(Ogre::Vector3 force)
{
	if (dynamic)
	{
		appliedForce += force;
	}
}