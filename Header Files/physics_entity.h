#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

class PhysicsEngine;

#include "entity.h"
#include "physics_engine.h"

enum ENTITY_BODY_TYPE
{
	ENTITY_BODY_METAPHYSICAL,
	ENTITY_BODY_METAPHYSICAL_RAY,
	ENTITY_BODY_RAY,
	ENTITY_BODY_METAPHYSICAL_SPHERE,
	ENTITY_BODY_SPHERE,
	ENTITY_BODY_BOX,
};

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity();
	virtual ~PhysicsEntity() = 0;
	virtual void cleanup(PhysicsEngine & physicsEngine);
	//detaches itself from the passed in physicsEngine
	virtual void detachFrom(PhysicsEngine &physicsEngine);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	void ApplyForce(float x, float y, float z);
	void ApplyForce(Ogre::Vector3 force);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity) = 0;

	// Getters and setters
	Ogre::Vector3 GetDeltaVelocity();
	Ogre::Vector3 GetPreviousVelocity();
	Ogre::Vector3 GetVelocity();
	float getSpeed(); //returns the velocitySquared (to save on computation)
	float GetMass();
	float GetRestitution();

	virtual void SetVelocity(Ogre::Vector3 v);

	Ogre::Vector3 GetAppliedForce();
	ENTITY_BODY_TYPE GetBodyType();
	bool IsAbsoluteGravitationalPull();
	bool IsDynamic();
	bool IsGravitational();

	virtual void SetBodyType(ENTITY_BODY_TYPE type);

	virtual float GetRadius();

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
