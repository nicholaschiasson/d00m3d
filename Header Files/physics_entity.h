#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include "entity.h"

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity();
	virtual ~PhysicsEntity() = 0;

	virtual void Update(const Ogre::FrameEvent &fe);
	
	void ApplyForce(float x, float y, float z);
	void ApplyForce(Ogre::Vector3 force);

private:
	Ogre::Vector3 acceleration;
	Ogre::Vector3 appliedForce;
	float mass;

	// For cheating the laws of physics
	bool dynamic;
	bool gravitational;

};

#endif // PHYSICS_ENTITY_H
