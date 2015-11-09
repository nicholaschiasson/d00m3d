#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft()
{
}

Spacecraft::~Spacecraft()
{
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* worldNode, PhysicsEngine &physicsEngine)
{
	PhysicsEntity::Initialize(sceneManager, worldNode, physicsEngine);

	Ogre::Entity *spacecraftBodyEntity = sceneManager->createEntity("Cone");
	spacecraftBodyEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftBodyNode = sceneNode->createChildSceneNode(Ogre::String("SpacecraftBody" + entityCount));
	spacecraftBodyNode->attachObject(spacecraftBodyEntity);
	spacecraftBodyNode->scale(1.0f, 1.0f, 0.25f);
	spacecraftBodyNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));

	laser.Initialize(sceneManager, sceneNode, physicsEngine);
}

void Spacecraft::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);
	if(alive){
		laser.Update(fe);
	}
}

void Spacecraft::fireLaser()
{
	if(laser.getState() == Laser::LASER_READY){
		laser.fire();
	}
}