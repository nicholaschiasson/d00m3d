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
	sceneManager = sceneMan;
	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = cam;
	num_asteroids_ = MAX_NUM_ASTEROIDS;
	//creating the player entitty
	player.Initialize(sceneManager, worldSceneNode);
	camera->attachTo(&player);
	camera->setDistance(Ogre::Vector3(0,1,2));
	
	//Setting up the basic control scheme
	initControls(inMan);

	// TEST CUBE IN THE CENTER OF THE WORLD
	
	Item myItem;
	myItem.Initialize(sceneManager, worldSceneNode);
	
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

void World::setupAsteroids()
{
	//Use to set position/orientation... of asteroids? just what the prof had.
    for (int i = 0; i < num_asteroids_; i++){
		
      //asteroid_[i].pos = Ogre::Vector3(-300 + 600 * (rand() % 1000) / 1000.0f, -300 + 600 * (rand() % 1000) / 1000.0f, 600 * (rand() % 1000) / 1000.0f);
      // asteroid_[i].pos = Ogre::Vector3(0 + i,0,0);
	  //asteroid_[i].ori = Ogre::Quaternion(1.0f, 3.14*(rand() % 1000) / 1000.0f, 3.14*(rand() % 1000) / 1000.0f, 3.14*(rand() % 1000) / 1000.0f);
	  //asteroid_[i].lm = Ogre::Quaternion(1.0f, 0.005*3.14*(rand() % 1000) / 1000.0f, 0.005*3.14*(rand() % 1000) / 1000.0f, 0.005*3.14*(rand() % 1000) / 1000.0f);
	  //asteroid_[i].drift = Ogre::Vector3(((double) rand() / RAND_MAX)*0.2, ((double) rand() / RAND_MAX)*0.2, ((double) rand() / RAND_MAX)*0.2);
    }

    Ogre::SceneNode* root_scene_node = sceneManager->getRootSceneNode();

        /* Create multiple entities of a mesh */
	Ogre::String entity_name, prefix("Asteroid");
  	for (int i = 0; i < num_asteroids_; i++){

		entity_name = prefix + Ogre::StringConverter::toString(i);
		asteroid_[i].Initialize(sceneManager,entity_name);
		asteroid_[i].getAsteroidSceneNode()->setPosition(i - 5,0,-i);

	} 
}


void World::createWorld()
{
	//TODO setup stuff for the world goes here.
}

void World::updateWorld(const Ogre::FrameEvent& fe)
{
	//TODO update stuff
	player.update();
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
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

		player->translate(playerDirection * fe.timeSinceLastFrame);
	}
}

void World::PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
		player->translate(-playerRight * fe.timeSinceLastFrame);
	}
}

void World::PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

		player->translate(-playerDirection * fe.timeSinceLastFrame);
	}
}

void World::PlayerMoveRight(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
		player->translate(playerRight * fe.timeSinceLastFrame);
	}
}

void World::PlayerMoveUp(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
		player->translate(playerUp * fe.timeSinceLastFrame);
	}
}

void World::PlayerMoveDown(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		Ogre::Quaternion playerOrientation = player->getOrientation();
		Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
		player->translate(-playerUp * fe.timeSinceLastFrame);
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