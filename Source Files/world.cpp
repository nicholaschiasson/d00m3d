//world.cpp

#include "world.h"

World::World(): worldSceneNode(NULL), camera(NULL), sceneManager(NULL), worldRadius(1000.0f)
{
	//lattahdah lattahdah
}

World::~World()
{
	//TODO memory cleanup
	JudgementDay();
}

void World::initWorld(Ogre::SceneManager* sceneMan, Camera* cam, InputManager* inMan)
{
	if(cam == NULL || inMan == NULL)
	{
		throw std::runtime_error("Camera or InputManager not initialized!");
	}

	sceneManager = sceneMan;
	sceneManager->setSkyDome(true, "SkyboxMaterial", 5, 8);
	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = cam;

	exists = true;
	worldRadius = 1000.0f;
	spawnTime = 2.0f;
	timer = spawnTime;

	
	// The source of all our frustrations
	blackHole.Initialize(sceneManager, worldSceneNode, physicsEngine);

	//creating the player entity
	player.Initialize(sceneManager, worldSceneNode, physicsEngine);
	camera->attachTo(&player);
	player.translate(0.0f, 0.0f, 300.0f);
	
	//Setting up the basic control scheme
	initControls(inMan);
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

void World::SpawnAsteroid()
{
	Asteroid *asteroid = new Asteroid();
	asteroid->Initialize(sceneManager, worldSceneNode, physicsEngine);
	float theta = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	float phi = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	Ogre::Vector3 initialPosition = Ogre::Vector3(cos(theta) * sin(phi), sin(theta) * sin(phi), -cos(phi)) * worldRadius;
	asteroid->translate(initialPosition);
	asteroids.push_back(asteroid);
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
		player.Update(fe);
		
		std::vector<unsigned int> deadAsteroidIndices;
		for (std::vector<Asteroid *>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
		{
			(*it)->Update(fe);
			if (!(*it)->isAlive())
			{
				deadAsteroidIndices.push_back((unsigned int)(it - asteroids.begin()));
			}
		}
		for (std::vector<unsigned int>::iterator it = deadAsteroidIndices.begin(); it != deadAsteroidIndices.end(); ++it)
		{
			std::vector<Asteroid *>::iterator deadIt = asteroids.begin() + (*it);
			Asteroid *dead = *deadIt;
			asteroids.erase(deadIt);
			physicsEngine.RemovePhysicsEntity(dead);
			delete dead;
		}

		if (timer <= 0.0f)
		{
			SpawnAsteroid();
			timer = spawnTime;
		}
		else
		{
			timer -= fe.timeSinceLastFrame;
		}

		physicsEngine.Update(fe); // I think this should always be updated last
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
	for (std::vector<Asteroid *>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
	{
		if (*it != 0)
		{
			delete *it;
			*it = 0;
		}
	}
	asteroids.clear();
}