#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "physics_entity.h"

class PhysicsEntity;

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(const Ogre::FrameEvent &fe);

	void AddPhysicsEntity(PhysicsEntity *physicsEntity);

private:
	std::vector<PhysicsEntity *> physicsEntities; 

};

#endif // SPHYSICS_ENGINE_H
