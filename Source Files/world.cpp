//world.cpp

#include "world.h"

World::World(): worldSceneNode(NULL), camera(NULL), sceneManager(NULL)
{
	//lattahdah lattahdah
}

World::~World()
{
	//TODO memory cleanup
}

void World::initWorld(Ogre::SceneManager* sceneMan, Camera* cam, InputManager* inMan)
{
	if(cam == NULL || inMan == NULL)
	{
		throw std::runtime_error("Camera or InputManager not initialized!");
	}
	exists = true;
	sceneManager = sceneMan;
	sceneManager->setSkyDome(true, "SkyboxMaterial", 5, 8);
	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = cam;
	num_asteroids_ = MAX_NUM_ASTEROIDS;

	//setupBlackHole();

	//creating the player entity
	player.Initialize(sceneManager, worldSceneNode, physicsEngine);
	camera->attachTo(&player);
	player.translate(0.0f, 0.0f, 100.0f);
	
	//Setting up the basic control scheme
	initControls(inMan);
	
	myItem.Initialize(sceneManager, worldSceneNode, physicsEngine);
	myItem.translate(0.0f, 0.0f, 3.0f);

	setupAsteroids();
}

/*
* Setting up the Controls
*/

void World::initControls(InputManager *inputManager)
{
	inputManager->RegisterCallback(this, PlayerMoveForward, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_W);
	inputManager->RegisterCallback(this, PlayerMoveLeft, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_A);
	inputManager->RegisterCallback(this, PlayerMoveBackward, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_S);
	inputManager->RegisterCallback(this, PlayerMoveRight, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_D);
	inputManager->RegisterCallback(this, PlayerMoveUp, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_Q);
	inputManager->RegisterCallback(this, PlayerMoveDown, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_C);
	inputManager->RegisterCallback(this, PlayerPitchUp, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_UP);
	inputManager->RegisterCallback(this, PlayerYawLeft, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_LEFT);
	inputManager->RegisterCallback(this, PlayerPitchDown, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_DOWN);
	inputManager->RegisterCallback(this, PlayerYawRight, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_RIGHT);
	inputManager->RegisterCallback(this, playerFireLaser, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_SPACE);
	
}

void World::setupBlackHole(){
	blackHole.Initialize(sceneManager, worldSceneNode, physicsEngine);
}

void World::setupAsteroids()
{
	//Use to set position/orientation... of asteroids? just what the prof had.
    for (int i = 0; i < num_asteroids_; i++){
		
      //asteroid_[i].pos = Ogre::Vector3(-300 + 600 * (rand() % 1000) / 1000.0f, -300 + 600 * (rand() % 1000) / 1000.0f, 600 * (rand() % 1000) / 1000.0f);
      //asteroid_[i].pos = Ogre::Vector3(0 + i,0,0);
	  //asteroid_[i].ori = Ogre::Quaternion(1.0f, 3.14*(rand() % 1000) / 1000.0f, 3.14*(rand() % 1000) / 1000.0f, 3.14*(rand() % 1000) / 1000.0f);
	  //asteroid_[i].lm = Ogre::Quaternion(1.0f, 0.005*3.14*(rand() % 1000) / 1000.0f, 0.005*3.14*(rand() % 1000) / 1000.0f, 0.005*3.14*(rand() % 1000) / 1000.0f);
	  //asteroid_[i].drift = Ogre::Vector3(((double) rand() / RAND_MAX)*0.2, ((double) rand() / RAND_MAX)*0.2, ((double) rand() / RAND_MAX)*0.2);
    }

        /* Create multiple entities of a mesh */
  	for (int i = 0; i < num_asteroids_; i++){

		asteroid_[i].Initialize(sceneManager, worldSceneNode, physicsEngine);
		asteroid_[i].translate((float)i - 5.0f, 0.0f, (float)-(i * 3.5));

	}
}

void World::createWorld()
{
	//TODO setup stuff for the world goes here.
}

void World::updateWorld(const Ogre::FrameEvent& fe)
{
	if (exists)
	{
		//TODO update stuff
		physicsEngine.Update(fe);
		player.Update(fe);
		myItem.Update(fe);
		for (int i = 0; i < num_asteroids_; i++)
		{
			asteroid_[i].Update(fe);
		}
	}
}

/*
* InputManger Callbacks
*/

void World::PlayerMoveForward(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World *>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersForward();
	}
}

void World::PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersLeft();
	}
}

void World::PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersBackward();
	}
}

void World::PlayerMoveRight(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersRight();
	}
}

void World::PlayerMoveUp(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersUpward();
	}
}

void World::PlayerMoveDown(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersDownward();
	}
}

void World::PlayerPitchUp(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->pitch(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerYawLeft(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->yaw(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerPitchDown(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->pitch(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerYawRight(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->yaw(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::playerFireLaser(void* context, const Ogre::FrameEvent& fe)
{
	if(context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->fireLaser();
	}
}

void World::JudgementDay()
{
	exists = false;
}