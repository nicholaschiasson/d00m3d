#include "item.h"

Item::Item()
{
}
Item::Item(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, Resource::RESOURCE_TYPE type, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, location, type, parentID);
}
Item::~Item()
{
}

void Item::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);
}

void Item::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, Ogre::Vector3(0,0,0), Resource::NONE, parentID);
}

void Item::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, Resource::RESOURCE_TYPE type, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	//setting our mass to 0
	mass = 40.0f;

	Ogre::Entity *itemEntity = sceneManager->createEntity("Cube");
	itemEntity->setMaterialName("ItemMaterial");
	sceneNode->attachObject(itemEntity);
	scale(0.25f, 0.25f, 0.25f);
	translate(location);

	myType = type;

	//TODO randomize?
	value = 5;
}

void Item::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{

}

void Item::Damage(float damage)
{
	// nope
}

int Item::getValue() const
{
	return value;
}

Resource Item::collect(Entity* entity)
{
	//we kill the item since we collected it.
	kill();
	return Resource(myType, 5.0);
}

float Item::GetRadius()
{
	return PhysicsEntity::GetRadius() * 25.0;
}