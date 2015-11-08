//world.cpp

#include "world.h"


World::World(): worldSceneNode(NULL)
{
	//lattahdah lattahdah
	player = new PlayerSpacecraft();
}

World::~World()
{
	//TODO memory cleanup
	delete player;
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
	// this won't work - this is creating a copy of the input manager passed in
	inputManager = *inMan;

	//creating the player entitty
	player->Initialize(sceneManager);
	
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