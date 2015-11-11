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
				if (i->GetBodyType() == ENTITY_BODY_SPHERE)
				{
					if ((*it)->GetBodyType() == ENTITY_BODY_SPHERE)
					{
						PerformSphereSphereCollisionTest(i, *it);
					}
					else if ((*it)->GetBodyType() == ENTITY_BODY_RAY)
					{
						PerformRaySphereCollisionTest(*it, i);
					}
				}
				else if (i->GetBodyType() == ENTITY_BODY_RAY)
				{
					if ((*it)->GetBodyType() == ENTITY_BODY_SPHERE)
					{
						PerformRaySphereCollisionTest(i, *it);
					}
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

void PhysicsEngine::PerformSphereSphereCollisionTest(PhysicsEntity *sphere1, PhysicsEntity *sphere2)
{
	float overlapMagnitude = (sphere1->GetRadius() + sphere2->GetRadius()) - sphere1->getPosition().distance(sphere2->getPosition());
	if (overlapMagnitude >= 0.0f)
	{
		Ogre::Vector3 d = sphere2->getPosition() - sphere1->getPosition();
		Ogre::Vector3 relativeVelocity = d * (d.dotProduct(sphere1->GetVelocity() - sphere2->GetVelocity()) / d.squaredLength());
		
		Ogre::Vector3 impulse1 = (((sphere2->GetRestitution() + 1.0f) * relativeVelocity) /
			((1 / sphere1->GetMass()) + (1 / sphere2->GetMass())));
		Ogre::Vector3 impulse2 = -(((sphere1->GetRestitution() + 1.0f) * relativeVelocity) /
			((1 / sphere1->GetMass()) + (1 / sphere2->GetMass())));
		
		//Ogre::Vector3 currentImpulse1 = d * (d.dotProduct(sphere1->GetAppliedForce()) / d.squaredLength());
		//Ogre::Vector3 currentImpulse2 = -d * (d.dotProduct(sphere2->GetAppliedForce()) / d.squaredLength());
		
		sphere1->translate(-d.normalisedCopy() * (overlapMagnitude / 2.0f));
		sphere2->translate(d.normalisedCopy() * (overlapMagnitude / 2.0f));

		sphere2->ApplyForce(impulse1);// + currentImpulse1);
		sphere1->ApplyForce(impulse2);// + currentImpulse2);

		sphere1->Collide(sphere2);
		sphere2->Collide(sphere1);
	}
}

void PhysicsEngine::PerformRaySphereCollisionTest(PhysicsEntity *ray, PhysicsEntity *sphere)
{
	Ogre::Vector3 rayDirection = ray->getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
}