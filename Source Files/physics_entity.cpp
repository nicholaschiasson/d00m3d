#include "physics_entity.h"

PhysicsEntity::PhysicsEntity()
{
	appliedForce = 0.0f;
	bodyType = ENTITY_BODY_SPHERE;
	dynamic = true;
	gravitational = false;
	mass = 1.0f;
	previousVelocity = 0.0f;
	velocity = 0.0f;
}

PhysicsEntity::~PhysicsEntity()
{
}

void PhysicsEntity::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine)
{
	Entity::Initialize(sceneManager, parentNode);
	physicsEngine.AddPhysicsEntity(this);
}

void PhysicsEntity::Update(const Ogre::FrameEvent &fe)
{
	if (dynamic)
	{
		if (mass != 0.0f)
		{
			previousVelocity = velocity;
			velocity += appliedForce / mass;
		}
		translate(velocity * fe.timeSinceLastFrame);
		appliedForce = 0;
	}
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

Ogre::Vector3 PhysicsEntity::GetDeltaVelocity()
{
	return velocity - previousVelocity;
}

float PhysicsEntity::GetMass()
{
	return mass;
}

ENTITY_BODY_TYPE PhysicsEntity::GetBodyType()
{
	return bodyType;
}

bool PhysicsEntity::IsDynamic()
{
	return dynamic;
}

bool PhysicsEntity::IsGravitational()
{
	return gravitational;
}