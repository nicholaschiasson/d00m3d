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
	void RemovePhysicsEntity(PhysicsEntity *physicsEntity);

	bool PerformSphereSphereCollisionTest(const Ogre::FrameEvent &fe, PhysicsEntity *sphere1, PhysicsEntity *sphere2);
	bool PerformRaySphereCollisionTest(const Ogre::FrameEvent &fe, PhysicsEntity *ray, PhysicsEntity *sphere);

private:
	float gravitationalConstant;
	std::vector<PhysicsEntity *> physicsEntities;

};

#endif // SPHYSICS_ENGINE_H
