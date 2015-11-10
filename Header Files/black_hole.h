#ifndef BLACK_HOLE_H
#define BLACK_HOLE_H

#include "entity.h"
#include "input_manager.h"

class BlackHole : public Entity
{
public:
	BlackHole();
	virtual ~BlackHole();
    virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *worldNode);
	Ogre::SceneNode* getSceneNode();
	float getSize();

private:
	float size;
	float gravitationalPull;
};

#endif // ASTEROID_H
