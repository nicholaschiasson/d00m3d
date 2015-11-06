//world.cpp

#include "world.h"

World::World(Ogre::SceneNode* rootNode/*, Camera* cam, InputManager* inMan*/): 
	worldSceneNode(rootNode->createChildSceneNode("_worldSceneNode_"))/*, camera(cam), inputManager(inMan) */ //note underscores so someone decided to create earth and label it worldSceneNode, wont have conflicts
{
	//lattahdah lattahdah
}

World::~World()
{
	//TODO memory cleanup
}

void World::initWorld()
{
	//TODO setup stuff for the world goes here.
}