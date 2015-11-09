#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include "entity.h"

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

	virtual void Update(const Ogre::FrameEvent &fe);
	
	void ApplyForce(float x, float y, float z);
	void ApplyForce(Ogre::Vector3 force);

protected:
	Ogre::Vector3 acceleration;
	Ogre::Vector3 appliedForce;
	float mass;

	// For cheating the laws of physics
	bool dynamic;
	bool gravitational;

private:

};

#endif // PHYSICS_ENTITY_H
