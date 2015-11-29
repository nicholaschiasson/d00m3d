#ifndef ITEM_H
#define ITEM_H

#include "physics_entity.h"
#include <OgreEntity.h>
#include "resource.h"

class Item: public PhysicsEntity
{
public:

	Item();
	Item(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, Resource::RESOURCE_TYPE type, unsigned int parentID = -1);
	~Item();

	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void Damage(float damage);

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 location, Resource::RESOURCE_TYPE type, unsigned int parentID = -1);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &PhysicsEngine, unsigned int parentID = -1);

	int getValue() const;

	virtual Resource collect(Entity* entity);	
	virtual float GetRadius();
private:
	int value;
	Resource::RESOURCE_TYPE myType;
};

#endif //ITEM_H