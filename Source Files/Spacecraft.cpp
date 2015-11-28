#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft() :
	thrusterForce(500.0f), weapon(new LaserCannon())
{
}

Spacecraft::~Spacecraft()
{
	
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	mass = 5000.0f;

	unsigned int pid = (parentID == -1 ? objectID : parentID);
	
	float spacecraftScaleX = 1.6f, spacecraftScaleY = 0.6f, spacecraftScaleZ = 1.0f;
	float invSpacecraftScaleX = 1.0f / spacecraftScaleX, invSpacecraftScaleY = 1.0f / spacecraftScaleY, invSpacecraftScaleZ = 1.0f / spacecraftScaleZ;
	Ogre::Entity *spacecraftBodyEntity = sceneManager->createEntity("Cylinder");
	spacecraftBodyEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftBodyNode = parentNode->createChildSceneNode("SpacecraftBody" + Ogre::StringConverter::toString(entityCount));
	spacecraftBodyNode->attachObject(spacecraftBodyEntity);
	spacecraftBodyNode->scale(0.75f, 0.75f, 0.75f);
	spacecraftBodyNode->scale(spacecraftScaleX, spacecraftScaleY, spacecraftScaleZ);
	spacecraftBodyNode->pitch(-Ogre::Radian(Ogre::Math::HALF_PI));

	Ogre::Entity *spacecraftLeftThrusterEntity = sceneManager->createEntity("Torus");
	spacecraftLeftThrusterEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftLeftThrusterNode = spacecraftBodyNode->createChildSceneNode("SpacecraftLeftThruster" + Ogre::StringConverter::toString(entityCount));
	spacecraftLeftThrusterNode->attachObject(spacecraftLeftThrusterEntity);
	spacecraftLeftThrusterNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftLeftThrusterNode->scale(0.4f, 0.4f, 2.0f);
	spacecraftLeftThrusterNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftLeftThrusterNode->translate(-0.1f, -0.3f, 0.0f);
	
	Ogre::Entity *spacecraftRightThrusterEntity = sceneManager->createEntity("Torus");
	spacecraftRightThrusterEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftRightThrusterNode = spacecraftBodyNode->createChildSceneNode("SpacecraftRightThruster" + Ogre::StringConverter::toString(entityCount));
	spacecraftRightThrusterNode->attachObject(spacecraftRightThrusterEntity);
	spacecraftRightThrusterNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftRightThrusterNode->scale(0.4f, 0.4f, 2.0f);
	spacecraftRightThrusterNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftRightThrusterNode->translate(0.1f, -0.3f, 0.0f);
	
	Ogre::Entity *spacecraftLeftWingEntity = sceneManager->createEntity("Pyramid");
	spacecraftLeftWingEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftLeftWingNode = spacecraftBodyNode->createChildSceneNode("SpacecraftLeftWing" + Ogre::StringConverter::toString(entityCount));
	spacecraftLeftWingNode->attachObject(spacecraftLeftWingEntity);
	spacecraftLeftWingNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftLeftWingNode->scale(0.8f, 0.5f, 0.3f);
	spacecraftLeftWingNode->roll(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftLeftWingNode->translate(-0.375f, 0.0f, 0.0f);
	
	Ogre::Entity *spacecraftRightWingEntity = sceneManager->createEntity("Pyramid");
	spacecraftRightWingEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftRightWingNode = spacecraftBodyNode->createChildSceneNode("SpacecraftRightWing" + Ogre::StringConverter::toString(entityCount));
	spacecraftRightWingNode->attachObject(spacecraftRightWingEntity);
	spacecraftRightWingNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftRightWingNode->scale(0.8f, 0.5f, 0.3f);
	spacecraftRightWingNode->roll(Ogre::Radian(-Ogre::Math::HALF_PI));
	spacecraftRightWingNode->translate(0.375f, 0.0f, 0.0f);

	Ogre::Entity *spacecraftNoseEntity = sceneManager->createEntity("Sphere");
	spacecraftNoseEntity->setMaterialName("PlayerSpacecraftMaterial");
	Ogre::SceneNode *spacecraftNoseNode = spacecraftBodyNode->createChildSceneNode("SpacecraftNose" + Ogre::StringConverter::toString(entityCount));
	spacecraftNoseNode->attachObject(spacecraftNoseEntity);
	spacecraftNoseNode->scale(0.502f, 1.5f, 0.502f);
	spacecraftNoseNode->translate(0.0f, 0.45f, 0.0f);
	
	Ogre::Entity *spacecraftPodEntity = sceneManager->createEntity("SphereScreen");
	spacecraftPodEntity->setMaterialName("PlayerSpacecraftPodMaterial");
	Ogre::SceneNode *spacecraftPodNode = spacecraftNoseNode->createChildSceneNode("SpacecraftPod" + Ogre::StringConverter::toString(entityCount));
	spacecraftPodNode->attachObject(spacecraftPodEntity);
	spacecraftPodNode->scale(0.6f, 0.5f, 0.5f);
	spacecraftPodNode->pitch(Ogre::Radian(-Ogre::Math::PI / 5.5f));
	spacecraftPodNode->translate(0.0f, 0.28f, 0.175f);

	weapon->Initialize(sceneManager, spacecraftBodyNode, physicsEngine, pid);
	weapon->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	weapon->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	weapon->translate(0.0f, 0.0f, -((0.25f * 0.5f) + ((0.75f * spacecraftScaleY) * 0.5f)));
	
}

void Spacecraft::Update(const Ogre::FrameEvent &fe)
{
	if(alive)
	{
		PhysicsEntity::Update(fe);
		weapon->Update(fe);
	}
}

void Spacecraft::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{

}

void Spacecraft::spaghettify()
{

}

void Spacecraft::fireLaser()
{
	if(weapon->getState() == Weapon::WEAPON_READY){
		weapon->fire();
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