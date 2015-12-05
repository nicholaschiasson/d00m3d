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
		if ((*it)->isAlive())
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
	}
	for (std::vector<PhysicsEntity *>::iterator it = dynamicEntities.begin(); it != dynamicEntities.end(); ++it)
	{
		for (std::vector<PhysicsEntity *>::iterator gr = gravitationalEntities.begin(); gr != gravitationalEntities.end(); ++gr)
		{
			if (*it != *gr)
			{
				Ogre::Vector3 distance = (*gr)->getPosition() - (*it)->getPosition();
				if (distance.squaredLength() != 0.0f)
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
			if (i != (*it) && i->isAlive() && (*it)->isAlive() && 
				//i->GetObjectID() != (*it)->GetObjectID() && i->GetParentID() != (*it)->GetParentID() &&
				i->GetObjectID() != (*it)->GetParentID() && i->GetParentID() != (*it)->GetObjectID())
			{
				if (i->GetBodyType() == ENTITY_BODY_SPHERE || i->GetBodyType() == ENTITY_BODY_METAPHYSICAL_SPHERE)
				{
					if ((*it)->GetBodyType() == ENTITY_BODY_SPHERE || (*it)->GetBodyType() == ENTITY_BODY_METAPHYSICAL_SPHERE)
					{
						PerformSphereSphereCollisionTest(fe, i, *it);
					}
					else if ((*it)->GetBodyType() == ENTITY_BODY_RAY || (*it)->GetBodyType() == ENTITY_BODY_METAPHYSICAL_RAY)
					{
						PerformRaySphereCollisionTest(fe, *it, i);
					}
				}
				else if (i->GetBodyType() == ENTITY_BODY_RAY || i->GetBodyType() == ENTITY_BODY_METAPHYSICAL_RAY)
				{
					if ((*it)->GetBodyType() == ENTITY_BODY_SPHERE || (*it)->GetBodyType() == ENTITY_BODY_METAPHYSICAL_SPHERE)
					{
						PerformRaySphereCollisionTest(fe, i, *it);
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

void PhysicsEngine::RemovePhysicsEntity(PhysicsEntity *physicsEntity)
{
	std::vector<PhysicsEntity *>::iterator remove = std::find(physicsEntities.begin(), physicsEntities.end(), physicsEntity);
	if (remove != physicsEntities.end())
	{
		physicsEntities.erase(remove);
	}
}

bool PhysicsEngine::PerformSphereSphereCollisionTest(const Ogre::FrameEvent &fe, PhysicsEntity *sphere1, PhysicsEntity *sphere2)
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
		
		if (sphere1->GetBodyType() == ENTITY_BODY_SPHERE && sphere2->GetBodyType() == ENTITY_BODY_SPHERE)
		{
			sphere1->translate(-d.normalisedCopy() * (overlapMagnitude / 2.0f));
			sphere2->translate(d.normalisedCopy() * (overlapMagnitude / 2.0f));

			sphere2->ApplyForce(impulse1);// + currentImpulse1);
			sphere1->ApplyForce(impulse2);// + currentImpulse2);
		}

		sphere1->Collide(fe, sphere2);
		sphere2->Collide(fe, sphere1);

		return true;
	}

	return false;
}

bool PhysicsEngine::PerformRaySphereCollisionTest(const Ogre::FrameEvent &fe, PhysicsEntity *ray, PhysicsEntity *sphere)
{
	Ogre::Vector3 rayDirection = ray->getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	Ogre::Vector3 rayPosition = ray->getDerivedPosition();

	float ab2 = rayDirection.dotProduct(rayDirection);

	Ogre::Vector3 p = sphere->getDerivedPosition();
	Ogre::Vector3 ap = p - rayPosition;
	float ap_dot_dir = ap.dotProduct(rayDirection);
	float t = ap_dot_dir / ab2;

	if (t < 0.0f) t = 0.0f;

	Ogre::Vector3 q = rayPosition + rayDirection * t;

	Ogre::Vector3 pq = q - p;

	float radius = sphere->GetRadius();
	float r2 = radius * radius;

	if (pq.dotProduct(pq) < r2)
	{
		ray->Collide(fe, sphere);
		if (ray->GetBodyType() == ENTITY_BODY_RAY)
		{
			// sphere only detects collisions with physical rays
			sphere->Collide(fe, ray);
		}

		return true;
	}

	return false;
}