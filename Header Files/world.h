#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include "camera.h"
#include "input_manager.h"

#include "physics_engine.h"
#include "player_spacecraft.h"
#include "enemy_spacecraft.h"
#include "asteroid.h"
#include "black_hole.h"
#include "item.h"
#include "TextRenderer.h"
#include "particle_engine.h"
#include "TextRenderer.h"
#include "star.h"
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
	//void initWorld(Ogre::SceneManager* sceneMan, Camera* cam, InputManager* inMan, Ogre::OverlayManager* overlay_manager);
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
	
	Ogre::SceneManager* sceneManager;
	Camera *camera;
	PhysicsEngine physicsEngine;
	ParticleEngine particleEngine;
	bool exists;
	float timer;
	float spawnTime;

    #define MAX_NUM_OBJECTS 100 
    #define MAX_NUM_ENEMIES 15

	
	int numObjects;
	int numEnemies;

	Star star;
	PlayerSpacecraft player;
	
	std::vector<PhysicsEntity *> projectileList;
	std::vector<Item *> itemList;
	std::vector<Asteroid *> asteroidList;
	std::vector<EnemySpacecraft*> fleet;

	void SpawnAsteroid(Ogre::Vector3);
	void checkDistance(Entity* entity);
	void checkEnemyDistance(Entity* entity);

	//setup the control schemes
	void initControls(InputManager *inputManager);
	void cleanupLists(bool cleanupNeeded = true);
	void setupEnemies();
	void initObjects();
	void SpawnEnemies();
	TextRenderer UI;

	// InputManager Callbacks
	static void PlayerMoveForward(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerMoveRight(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerMoveUp(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerMoveDown(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerPitchUp(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerYawLeft(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerPitchDown(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerYawRight(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerRollCounterClockwise(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void PlayerRollClockwise(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void playerFireLaser(void* context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	static void test(void* context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);
	
	static void PlayerRotate(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2);

};

#endif