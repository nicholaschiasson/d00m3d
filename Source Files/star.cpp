#include "star.h"

Star::Star(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}
Star::Star()
{
}
Star::~Star()
{
}
void Star::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	bodyType = ENTITY_BODY_METAPHYSICAL_SPHERE;
	mass = 100000.0f;

	Ogre::Entity *StarEntity = sceneManager->createEntity("Sphere");
	StarEntity->setMaterialName("StarMaterial");
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Star" + Ogre::StringConverter::toString(entityCount));
	scale(500, 500, 500);
	sceneNode->attachObject(StarEntity);
}

void Star::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	Ogre::Vector3 distance = sceneNode->getPosition() - physicsEntity->getPosition();
	float points =0;
	if(distance.squaredLength() <= Ogre::Math::Sqr(PhysicsEntity::GetRadius())){
		physicsEntity->kill();
	}
	else{
		//damage should be half of what the collect will return
		physicsEntity->Damage(calcRadiation(physicsEntity)/2.0);
	}
}

float Star::GetRadius()
{
	return PhysicsEntity::GetRadius() + 1000.0;
}
Resource Star::collect(Entity* entity)
{
	return Resource(Resource::ENERGY, calcRadiation(entity));
}

float Star::calcRadiation(Entity* entity)
{
	float value = 0.0;
	Ogre::Vector3 distance = sceneNode->getPosition() - entity->getPosition();
	value = distance.length() - PhysicsEntity::GetRadius(); //max should be 1000 on the edge of the radiation range
	value = value/ 100.0; //making the max be 100.
	value = 100.0 - value; //if we are the edge we only get 1, every 10 closer it increases by 1.
	return value;
}