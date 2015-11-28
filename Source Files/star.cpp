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
	mass = 10000000000000000.0f; // SUBJECT TO TWEAKING!!!
	gravitational = true;

	Ogre::Entity *starEntity = sceneManager->createEntity("Sphere");
	starEntity->setMaterialName("StarMaterial");
	Ogre::SceneNode *asteroidNode = sceneNode->createChildSceneNode("Star" + Ogre::StringConverter::toString(entityCount));
	scale(1000, 1000, 1000);
	sceneNode->attachObject(starEntity);
}

void Star::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->kill();
	std::cout << " STAR : COLLISSION COLLISSIOON COLLISSION " <<std::endl;
}

float Star::GetRadius()
{
	return PhysicsEntity::GetRadius();// + 500;

}