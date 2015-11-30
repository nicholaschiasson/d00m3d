#include "weapon.h"

Weapon::Weapon() : materialPrefix("Laser"), timer(0), cooldown(5), myState(WEAPON_READY)
{
}

Weapon::~Weapon()
{
}

void Weapon::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	
	//setting our mass to 0
	bodyType = ENTITY_BODY_METAPHYSICAL;
	dynamic = false;
	mass = 0.0f;

	Ogre::Entity *cannonPivotEntity = sceneManager->createEntity("Sphere");
	cannonPivotEntity->setMaterialName(materialPrefix + "CannonMaterial");
	Ogre::SceneNode *cannonPivotNode = sceneNode->createChildSceneNode("CannonPivot" + Ogre::StringConverter::toString(entityCount));
	cannonPivotNode->attachObject(cannonPivotEntity);
	cannonPivotNode->scale(0.25f, 0.25f, 0.25f);

	Ogre::Entity *cannonBarrelEntity = sceneManager->createEntity("Torus");
	cannonBarrelEntity->setMaterialName(materialPrefix + "CannonMaterial");
	barrel = cannonPivotNode->createChildSceneNode("CannonBarrel" + Ogre::StringConverter::toString(entityCount));
	barrel->attachObject(cannonBarrelEntity);
	barrel->scale(1.0f / 0.25f, 1.0f / 0.25f, 1.0f / 0.25f);
	barrel->scale(0.25f, 0.25f, 1.5f);
	barrel->translate(0.0f, 0.0f, -0.75f);
}

void Weapon::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{

}

int Weapon::getCooldown() const
{
	return cooldown;
}

Weapon::WEAPON_STATE Weapon::getState()
{
	return myState;
}