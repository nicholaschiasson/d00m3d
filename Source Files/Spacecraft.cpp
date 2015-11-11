#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft()
{
}

Spacecraft::~Spacecraft()
{
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	mass = 5000.0f;
	//dynamic = false; // temp

	Ogre::Entity *spacecraftBodyEntity = sceneManager->createEntity("Cone");
	spacecraftBodyEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftBodyNode = sceneNode->createChildSceneNode("SpacecraftBody" + Ogre::StringConverter::toString(entityCount));
	spacecraftBodyNode->attachObject(spacecraftBodyEntity);
	spacecraftBodyNode->scale(1.0f, 1.0f, 0.25f);
	spacecraftBodyNode->pitch(Ogre::Radian(-(Ogre::Math::HALF_PI * 0.9f)));

	laser.Initialize(sceneManager, sceneNode, physicsEngine, objectID);
	
	thrusterForce = 500.0f;
}

void Spacecraft::Update(const Ogre::FrameEvent &fe)
{
	if(alive)
	{
		PhysicsEntity::Update(fe);
		laser.Update(fe);
	}
}

void Spacecraft::fireLaser()
{
	if(laser.getState() == Laser::LASER_READY){
		laser.fire();
	}
}

void Spacecraft::ThrustersForward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

	ApplyForce(playerDirection.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersLeft()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
	ApplyForce(-playerRight.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersBackward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

	ApplyForce(-playerDirection.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersRight()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
	ApplyForce(playerRight.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersUpward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
	ApplyForce(playerUp.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersDownward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
	ApplyForce(-playerUp.normalisedCopy() * thrusterForce);
}