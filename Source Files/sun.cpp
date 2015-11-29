#include "sun.h"

Sun::Sun(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}
Sun::Sun()
{
}
Sun::~Sun()
{
}
void Sun::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	bodyType = ENTITY_BODY_METAPHYSICAL_SPHERE;
	mass = 100000.0f;

	Ogre::Entity *sunEntity = sceneManager->createEntity("Sphere");
	sunEntity->setMaterialName("SunMaterial");
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Sun" + Ogre::StringConverter::toString(entityCount));
	scale(500, 500, 500);
	sceneNode->attachObject(sunEntity);
}

void Sun::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	Ogre::Vector3 distance = sceneNode->getPosition() - physicsEntity->getPosition();
	if(distance.squaredLength() <= Ogre::Math::Sqr(PhysicsEntity::GetRadius())){
		physicsEntity->kill();
	}
	else{
		std::cout << "COLLIDE!" <<std::endl;
	}
}

float Sun::GetRadius()
{
	return PhysicsEntity::GetRadius() + 1000.0;

}