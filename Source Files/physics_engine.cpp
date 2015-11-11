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
			if (*it != *gr)
			{
				Ogre::Vector3 distance = (*gr)->getPosition() - (*it)->getPosition();
				if (distance.length() != 0.0f)
				{
					Ogre::Vector3 force = distance.normalisedCopy() *
						gravitationalConstant * (((*it)->GetMass() * (*gr)->GetMass()) /
						((*gr)->IsAbsoluteGravitationalPull() ? ((*gr)->GetRadius() + (*it)->GetRadius()) : distance.squaredLength()));
					(*it)->ApplyForce(force);
					if ((*gr)->IsDynamic())
					{
						(*gr)->ApplyForce(force);
					}
				}
			}
		}
	}
	while (collidableEntities.size() > 0)
	{
		PhysicsEntity *i = collidableEntities.back();

		for (std::vector<PhysicsEntity *>::reverse_iterator it = collidableEntities.rbegin(); it != collidableEntities.rend(); ++it)
		{
			if (i != (*it) && i->GetObjectID() != (*it)->GetParentID() && i->GetParentID() != (*it)->GetObjectID())
			{
				float overlapMagnitude = (i->GetRadius() + (*it)->GetRadius()) - i->getPosition().distance((*it)->getPosition());
				if (overlapMagnitude >= 0.0f)
				{
					Ogre::Vector3 d = (*it)->getPosition() - i->getPosition();
					Ogre::Vector3 relativeVelocity = d * (d.dotProduct(i->GetVelocity() + (*it)->GetVelocity()) / d.squaredLength());
					
					Ogre::Vector3 impulse1 = -((((*it)->GetRestitution() + 1.0f) * relativeVelocity) /
						((1 / i->GetMass()) + (1 / (*it)->GetMass())));
					Ogre::Vector3 impulse2 = (((i->GetRestitution() + 1.0f) * relativeVelocity) /
						((1 / i->GetMass()) + (1 / (*it)->GetMass())));
					
					//Ogre::Vector3 currentImpulse1 = d * (d.dotProduct(i->GetAppliedForce()) / d.squaredLength());
					//Ogre::Vector3 currentImpulse2 = -d * (d.dotProduct((*it)->GetAppliedForce()) / d.squaredLength());

					(*it)->ApplyForce(impulse1);// + currentImpulse1);
					i->ApplyForce(impulse2);// + currentImpulse2);

					i->Collide(*it);
					(*it)->Collide(i);
				}
			}
		}
		collidableEntities.pop_back();
	}
}

void PhysicsEngine::AddPhysicsEntity(PhysicsEntity *physicsEntity)
{
	physicsEntities.push_back(physicsEntity);
}