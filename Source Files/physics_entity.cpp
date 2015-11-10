#include "physics_entity.h"

#include "defines.h"

PhysicsEntity::PhysicsEntity()
{
}

PhysicsEntity::~PhysicsEntity()
{
}

void PhysicsEntity::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Entity::Initialize(sceneManager, parentNode, parentID);
	physicsEngine.AddPhysicsEntity(this);
	absoluteGravitationalPull = false;
	appliedForce = 0.0f;
	bodyType = ENTITY_BODY_SPHERE;
	dynamic = true;
	gravitational = false;
	mass = 1.0f;
	restitution = 0.0f;
	previousVelocity = 0.0f;
	velocity = 0.0f;
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

void PhysicsEntity::Collide(PhysicsEntity *physicsEntity)
{
	// Should be overridden, probably pure virtual
	// DO NOT CALL THE OTHER PHYSICS ENTITY'S COLLIDE FUNCTION
	// That is for the caller of this function to do
}

Ogre::Vector3 PhysicsEntity::GetDeltaVelocity()
{
	return velocity - previousVelocity;
}

Ogre::Vector3 PhysicsEntity::GetPreviousVelocity()
{
	return previousVelocity;
}

Ogre::Vector3 PhysicsEntity::GetVelocity()
{
	return velocity;
}

float PhysicsEntity::GetMass()
{
	return mass;
}

float PhysicsEntity::GetRestitution()
{
	return restitution;
}

ENTITY_BODY_TYPE PhysicsEntity::GetBodyType()
{
	return bodyType;
}

bool PhysicsEntity::IsAbsoluteGravitationalPull()
{
	return absoluteGravitationalPull;
}

bool PhysicsEntity::IsDynamic()
{
	return dynamic;
}

bool PhysicsEntity::IsGravitational()
{
	return gravitational;
}

float PhysicsEntity::GetRadius()
{
	Ogre::Vector3 scale = sceneNode->getScale();
	return max(scale.x, max(scale.y, scale.z)) / 2.25f;
}