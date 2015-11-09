#include "item.h"

Item::Item()
{
}
Item::~Item()
{
}

void Item::update()
{
}

void Item::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode)
{
	Initialize(sceneManager, parentNode, Ogre::Vector3(0,0,0), FAKE);
}

void Item::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::Vector3 location, ITEM_TYPE type)
{
	//setting our mass to 0
	mass = 0.0;
	sceneNode = parentNode->createChildSceneNode("item");

	Ogre::Entity *itemEntity = sceneManager->createEntity("Cube");
	itemEntity->setMaterialName("ItemMaterial");
	sceneNode->attachObject(itemEntity);
	sceneNode->scale(0.1f, 0.1f, 0.1f);
	sceneNode->translate(location);

	myType = type;

	//TODO randomize?
	value = 5;
}

int Item::getValue() const
{
	return value;
}

Item::ITEM_TYPE Item::getType()
{
	return myType;
}