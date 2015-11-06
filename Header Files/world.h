#ifndef WORLD_H
#define WORLD_H

#include "ogre_application.h"

class World
{
public:
	World(Ogre::SceneNode* rootNode); //only creates a new sceneNode for the World, please use init to setup the world
	~World();

	/*	initWorld()
	*	Initializes the world to default.
	*/
	void initWorld();

private:
	//things in the world go here.
	Ogre::SceneNode* worldSceneNode;

};

#endif