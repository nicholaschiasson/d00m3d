//world.cpp

#include "world.h"


World::World(): worldSceneNode(NULL)
{
	//lattahdah lattahdah
}

World::~World()
{
	//TODO memory cleanup
}

void World::createWorld()
{
	//TODO setup stuff for the world goes here.
}

void World::initWorld(Ogre::SceneNode* rootNode, Camera* cam, InputManager* inMan)
{
	if(cam == NULL || inMan == NULL)
	{
		throw std::runtime_error("Camera or InputManager not initialized!");
	}
	worldSceneNode = rootNode->createChildSceneNode("_worldSceneNode_");
	camera = *cam;
	inputManager = *inMan;

}