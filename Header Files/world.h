#ifndef WORLD_H
#define WORLD_H

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "camera.h"
#include "input_manager.h"

#include "player_spacecraft.h"

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
	
	Ogre::SceneManager* sceneManager;
	Camera *camera;

	PlayerSpacecraft player;
	//setup the control schemes
	void initControls(InputManager *inputManager);
	void setupAsteroids();

	// InputManager Callbacks
	static void PlayerMoveForward(void *context, const Ogre::FrameEvent& fe);
	static void PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe);
	static void PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe);
	static void PlayerMoveRight(void *context, const Ogre::FrameEvent& fe);
	static void PlayerMoveUp(void *context, const Ogre::FrameEvent& fe);
	static void PlayerMoveDown(void *context, const Ogre::FrameEvent& fe);
	static void PlayerPitchUp(void *context, const Ogre::FrameEvent& fe);
	static void PlayerYawLeft(void *context, const Ogre::FrameEvent& fe);
	static void PlayerPitchDown(void *context, const Ogre::FrameEvent& fe);
	static void PlayerYawRight(void *context, const Ogre::FrameEvent& fe);

};

#endif