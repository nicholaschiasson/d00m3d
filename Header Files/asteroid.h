#ifndef ASTEROID_H
#define ASTEROID_H

#include "physics_entity.h"
#include "input_manager.h"

class Asteroid : public PhysicsEntity
{
public:
	Asteroid();
	Asteroid(Ogre::SceneManager *sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual ~Asteroid();

    virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsentity);
	
private:

};

#endif // ASTEROID_H
