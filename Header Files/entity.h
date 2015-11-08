#ifndef ENTITY_H
#define ENTITY_H

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"

class Entity
{
public:
	Entity();
	virtual ~Entity() = 0;

	virtual void Initialize(Ogre::SceneManager *sceneManager) = 0;
	//virtual void Update() = 0;

protected:
	Ogre::SceneNode *sceneNode;

private:
	float health;
	float durability;

};

#endif // ENTITY_H
