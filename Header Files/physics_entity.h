#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include "entity.h"
#include "physics_engine.h"

class PhysicsEngine;

enum ENTITY_BODY_TYPE
{
	ENTITY_BODY_METAPHYSICAL,
	ENTITY_BODY_RAY,
	ENTITY_BODY_SPHERE,
	ENTITY_BODY_PRISM,
};

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity();
	virtual ~PhysicsEntity() = 0;
	
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	void ApplyForce(float x, float y, float z);
	void ApplyForce(Ogre::Vector3 force);

	void Collide(PhysicsEntity *physicsEntity);

	// Getters and setters
	Ogre::Vector3 GetDeltaVelocity();
	Ogre::Vector3 GetPreviousVelocity();
	Ogre::Vector3 GetVelocity();
	float GetMass();
	float GetRestitution();

	ENTITY_BODY_TYPE GetBodyType();
	bool IsAbsoluteGravitationalPull();
	bool IsDynamic();
	bool IsGravitational();

	float GetRadius();

protected:
	Ogre::Vector3 appliedForce;
	float mass;
	float restitution;
	Ogre::Vector3 previousVelocity;
	Ogre::Vector3 velocity;

	// For cheating the laws of physics
	bool absoluteGravitationalPull;
	ENTITY_BODY_TYPE bodyType;
	bool dynamic;
	bool gravitational;

private:

};

#endif // PHYSICS_ENTITY_H
