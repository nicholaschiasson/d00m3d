#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include "entity.h"

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity();
	virtual ~PhysicsEntity() = 0;

protected:
	float mass;
private:

};

#endif // PHYSICS_ENTITY_H
