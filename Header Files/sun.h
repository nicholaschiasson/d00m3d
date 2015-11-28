#ifndef SUN_H
#define SUN_H

#include "physics_entity.h"
#include <OgreEntity.h>

class Sun: public PhysicsEntity{
public:
	Sun(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	Sun();
	~Sun();
	void Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	float GetRadius();
private:
};

#endif //SUN_H