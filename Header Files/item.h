#ifndef ITEM_H
#define ITEM_H

#include "physics_entity.h"
#include <OgreEntity.h>

class Item: public PhysicsEntity
{
public:
	Item();
	~Item();

	enum ITEM_TYPE{
		FUEL,
		ENERGY,
		FAKE
	};

	ITEM_TYPE getType();
	void update();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::Vector3 location, ITEM_TYPE type);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode);

	int getValue() const;

	

private:
	int value;
	ITEM_TYPE myType;
};

#endif //ITEM_H