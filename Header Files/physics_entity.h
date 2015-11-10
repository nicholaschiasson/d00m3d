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
	
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	void ApplyForce(float x, float y, float z);
	void ApplyForce(Ogre::Vector3 force);

	// Getters and setters
	Ogre::Vector3 GetDeltaVelocity();
	float GetMass();

	ENTITY_BODY_TYPE GetBodyType();
	bool IsDynamic();
	bool IsGravitational();

protected:
	Ogre::Vector3 appliedForce;
	float mass;
	Ogre::Vector3 previousVelocity;
	Ogre::Vector3 velocity;

	// For cheating the laws of physics
	ENTITY_BODY_TYPE bodyType;
	bool dynamic;
	bool gravitational;

private:

};

#endif // PHYSICS_ENTITY_H
