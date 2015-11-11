#ifndef ITEM_H
#define ITEM_H

#include "physics_entity.h"
#include <OgreEntity.h>

class Item: public PhysicsEntity
{
public:
	enum ITEM_TYPE{
		FUEL,
		ENERGY,
		FAKE
	};
	
	Item();
	Item(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, ITEM_TYPE type, unsigned int parentID = -1);
	~Item();

	ITEM_TYPE getType();
	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void Damage(float damage);

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, ITEM_TYPE type, unsigned int parentID = -1);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &PhysicsEngine, unsigned int parentID = -1);

	int getValue() const;

	

private:
	int value;
	ITEM_TYPE myType;
};

#endif //ITEM_H