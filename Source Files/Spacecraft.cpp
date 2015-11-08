#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft()
{
}

Spacecraft::~Spacecraft()
{
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* worldNode)
{
	sceneNode = worldNode->createChildSceneNode("Spacecraft");

	Ogre::Entity *spacecraftBodyEntity = sceneManager->createEntity("Cone");
	spacecraftBodyEntity->setMaterialName("ObjectMaterial");
	Ogre::SceneNode *spacecraftBodyNode = sceneNode->createChildSceneNode("SpacecraftBody");
	spacecraftBodyNode->attachObject(spacecraftBodyEntity);
	spacecraftBodyNode->scale(1.0f, 1.0f, 0.25f);
	spacecraftBodyNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
}