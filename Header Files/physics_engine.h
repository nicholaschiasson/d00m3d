#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

class PhysicsEntity;

#include <vector>
#include "physics_entity.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Update(const Ogre::FrameEvent &fe);

	void AddPhysicsEntity(PhysicsEntity *physicsEntity);

	bool PerformSphereSphereCollisionTest(PhysicsEntity *sphere1, PhysicsEntity *sphere2);
	bool PerformRaySphereCollisionTest(PhysicsEntity *ray, PhysicsEntity *sphere);

private:
	float gravitationalConstant;
	std::vector<PhysicsEntity *> physicsEntities;

};

#endif // SPHYSICS_ENGINE_H
