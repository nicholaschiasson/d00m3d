#ifndef WORLD_H
#define WORLD_H

#include <OgreSceneManager.h>

#include "camera.h"
#include "input_manager.h"

class World
{
public:
	World();
	~World();

	/*	initWorld()
	*	in:			SceneNode, the root Scene node of ogre
	*	in:			A Camera that has already been previously initialized
	*	in:			InputMangaer that has already been initialized
	*	Purpose:	To give the world all the correct data
	*/
	void initWorld(Ogre::SceneManager* sceneMan, Camera* cam, InputManager* inMan);
	
	/*	createWorld()
	*	
	*/
	void createWorld();

private:
	//things in the world go here.
	Ogre::SceneNode* worldSceneNode;
	
	Camera camera;
	InputManager inputManager;
	Ogre::SceneManager* sceneManager;

	//TODO REPLACE WITH PLAYERSPACESHIP

	//setup the control schemes
	void initControls();
	void setupAsteroids();

};

#endif