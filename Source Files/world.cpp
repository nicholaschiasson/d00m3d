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

void World::initWorld(Ogre::SceneManager* sceneMan, Camera* cam, InputManager* inMan)
{
	if(cam == NULL || inMan == NULL)
	{
		throw std::runtime_error("Camera or InputManager not initialized!");
	}
	sceneManager = sceneMan;
	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = *cam;
	inputManager = *inMan;

	//creating the player entitty
	//TODO REPLACE WITH THE PLAYERSAPCE SHIP
	
	//Setting up the basic control scheme
	initControls();
}

/*
* Setting up the Controls
*/

void World::initControls()
{
}

void World::setupAsteroids()
{
}