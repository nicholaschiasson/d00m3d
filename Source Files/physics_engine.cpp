#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
{
	gravitationalConstant = 6.674f * pow(10.0f, -11.0f);
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Update(const Ogre::FrameEvent &fe)
{
	std::vector<PhysicsEntity *> gravitationalEntities;
	std::vector<PhysicsEntity *> dynamicEntities;
	std::vector<PhysicsEntity *> collidableEntities;
	for (std::vector<PhysicsEntity *>::iterator it = physicsEntities.begin(); it != physicsEntities.end(); ++it)
	{
		if ((*it)->IsGravitational())
		{
			gravitationalEntities.push_back(*it);
		}
		if ((*it)->IsDynamic())
		{
			dynamicEntities.push_back(*it);
		}
		if ((*it)->GetBodyType() != ENTITY_BODY_METAPHYSICAL)
		{
			collidableEntities.push_back(*it);
		}
	}
	for (std::vector<PhysicsEntity *>::iterator it = dynamicEntities.begin(); it != dynamicEntities.end(); ++it)
	{
		for (std::vector<PhysicsEntity *>::iterator gr = gravitationalEntities.begin(); gr != gravitationalEntities.end(); ++gr)
		{
			Ogre::Vector3 distance = (*gr)->getPosition() - (*it)->getPosition();
			if (*it != *gr && distance.length() != 0.0f)
			{
				Ogre::Vector3 force = distance.normalisedCopy() *
					gravitationalConstant * (((*it)->GetMass() * (*gr)->GetMass()) / distance.squaredLength());
				(*it)->ApplyForce(force);
				if ((*gr)->IsDynamic())
				{
					(*gr)->ApplyForce(force);
				}
			}
		}
	}
	while (collidableEntities.size() > 0)
	{
		PhysicsEntity *i = collidableEntities.back();

		for (std::vector<PhysicsEntity *>::reverse_iterator it = collidableEntities.rbegin(); it != collidableEntities.rend(); ++it)
		{
			
		}

		collidableEntities.pop_back();
	}
}

void PhysicsEngine::AddPhysicsEntity(PhysicsEntity *physicsEntity)
{
	physicsEntities.push_back(physicsEntity);
}