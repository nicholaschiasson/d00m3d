#ifndef BLACK_HOLE_H
#define BLACK_HOLE_H

#include "physics_entity.h"
#include "input_manager.h"

class BlackHole : public PhysicsEntity
{
public:
	BlackHole();
	virtual ~BlackHole();
    virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void Damage(float damage);

	Ogre::SceneNode* getSceneNode();
	float getSize();

private:
	float size;
	float gravitationalPull;
};

#endif // ASTEROID_H
