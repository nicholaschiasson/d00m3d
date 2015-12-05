#include "weapon.h"

Weapon::Weapon() : materialPrefix("Laser"), timer(0), cooldown(5), myState(WEAPON_READY), sceneManager(0), worldNode(0), physicsEngine(0), particleEngine(0), energyRequirement(0.0f)
{
}

Weapon::~Weapon()
{
}

void Weapon::Initialize(Ogre::SceneManager *sm, Ogre::SceneNode* parentNode, Ogre::SceneNode *world, PhysicsEngine &ph, ParticleEngine *pe, unsigned int parentID)
{
	PhysicsEntity::Initialize(sm, parentNode, ph, parentID);
	
	//setting our mass to 0
	bodyType = ENTITY_BODY_METAPHYSICAL;
	dynamic = false;
	mass = 0.0f;

	sceneManager = sm;
	worldNode = world;
	physicsEngine = &ph;
	particleEngine = pe;

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

void Weapon::Update(const Ogre::FrameEvent &fe, Ogre::Vector3 v)
{
	PhysicsEntity::Update(fe);
	relativeVelocity = v;
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

float Weapon::getEnergyRequirement() const
{
	return energyRequirement;
}