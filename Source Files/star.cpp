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
	if(distance.squaredLength() <= Ogre::Math::Sqr(PhysicsEntity::GetRadius())){
		physicsEntity->kill();
	}
	else{
		std::cout << "COLLIDE!" <<std::endl;
	}
}

float Star::GetRadius()
{
	return PhysicsEntity::GetRadius() + 1000.0;
}