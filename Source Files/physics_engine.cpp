#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Update(const Ogre::FrameEvent &fe)
{
	for (std::vector<PhysicsEntity *>::iterator it = physicsEntities.begin(); it != physicsEntities.end(); ++it)
	{
		(*it)->Update(fe);
	}
}

void PhysicsEngine::AddPhysicsEntity(PhysicsEntity *physicsEntity)
{
	physicsEntities.push_back(physicsEntity);
}