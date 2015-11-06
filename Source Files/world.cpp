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

void World::initWorld(Ogre::SceneNode* rootNode, Camera* cam/*, InputManager* inMan*/)
{
	worldSceneNode = rootNode->createChildSceneNode("_worldSceneNode_");
	camera = *cam;

}