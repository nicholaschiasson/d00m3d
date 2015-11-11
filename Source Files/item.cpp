#include "item.h"

Item::Item()
{
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
	Initialize(sceneManager, parentNode, physicsEngine, Ogre::Vector3(0,0,0), FAKE, parentID);
}

void Item::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, ITEM_TYPE type, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	//setting our mass to 0
	mass = 40.0f;

	Ogre::Entity *itemEntity = sceneManager->createEntity("Cube");
	itemEntity->setMaterialName("ItemMaterial");
	sceneNode->attachObject(itemEntity);
	scale(0.1f, 0.1f, 0.1f);
	translate(location);

	myType = type;

	//TODO randomize?
	value = 5;
}

void Item::Collide(PhysicsEntity *physicsEntity)
{

}

int Item::getValue() const
{
	return value;
}

Item::ITEM_TYPE Item::getType()
{
	return myType;
}