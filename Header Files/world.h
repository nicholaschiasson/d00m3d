#ifndef WORLD_H
#define WORLD_H

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "camera.h"
#include "input_manager.h"

#include "physics_engine.h"
#include "player_spacecraft.h"
#include "asteroid.h"
#include "black_hole.h"
#include "item.h"


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
	/*	updateWorld()
	*
	*/
	void updateWorld(const Ogre::FrameEvent& fe);

	/*
						 .ed"""" """$$$$be.
					   -"           ^""**$$$e.
					 ."                   '$$$c
					/                      "4$$b
				   d  3                      $$$$
				   $  *                   .$$$$$$
				  .$  ^c           $$$$$e$$$$$$$$.
				  d$L  4.         4$$$$$$$$$$$$$$b
				  $$$$b ^ceeeee.  4$$ECL.F*$$$$$$$
	  e$""=.      $$$$P d$$$$F $ $$$$$$$$$- $$$$$$
	 z$$b. ^c     3$$$F "$$$$b   $"$$$$$$$  $$$$*"      .=""$c
	4$$$$L        $$P"  "$$b   .$ $$$$$...e$$        .=  e$$$.
	^*$$$$$c  %..   *c    ..    $$ 3$$$$$$$$$$eF     zP  d$$$$$
	  "**$$$ec   "   %ce""    $$$  $$$$$$$$$$*    .r" =$$$$P""
			"*$b.  "c  *$e.    *** d$$$$$"L$$    .d"  e$$***"
			  ^*$$c ^$c $$$      4J$$$$$% $$$ .e*".eeP"
				 "$$$$$$"'$=e....$*$$**$cz$$" "..d$*"
				   "*$$$  *=%4.$ L L$ P3$$$F $$$P"
					  "$   "%*ebJLzb$e$$$$$b $P"
						%..      4$$$$$$$$$$ "
						 $$$e   z$$$$$$$$$$%
						  "*$c  "$$$$$$$P"
						   ."""*$$$$$$$$bc
						.-"    .$***$$$"""*e.
					 .-"    .e$"     "*$c  ^*b.
			  .=*""""    .e$*"          "*bc  "*$e..
			.$"        .z*"               ^*$e.   "*****e.
			$$ee$c   .d"                     "*$.        3.
			^*$E")$..$"                         *   .ee==d%
			   $.d$$$*                           *  J$$$e*
				"""""                              "$$$"
	*/
	void JudgementDay();

private:
	//things in the world go here.
	Ogre::SceneNode* worldSceneNode;
	
	bool exists;
	Ogre::SceneManager* sceneManager;
	Camera *camera;
	PhysicsEngine physicsEngine;

	PlayerSpacecraft player;

	BlackHole blackHole;
	Item myItem;
	//setup the control schemes
	void initControls(InputManager *inputManager);

	void setupAsteroids();
	void setupBlackHole();

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


	#define MAX_NUM_ASTEROIDS 50
	int num_asteroids_;
    Asteroid asteroid_[MAX_NUM_ASTEROIDS];
	Ogre::SceneNode* cube_[MAX_NUM_ASTEROIDS];

	static void playerFireLaser(void* context, const Ogre::FrameEvent& fe);


};

#endif