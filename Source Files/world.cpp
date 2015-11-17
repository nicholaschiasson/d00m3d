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
//	sceneManager->setSkyDome(true, "SkyboxMaterial", 2, 9);
	sceneManager->setSkyBox(true, "SkyboxMaterial", 550, true);

	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = cam;

	exists = true;
	worldRadius = 1000.0f;
	spawnTime = 2.0f;
	timer = spawnTime;

	//tr = new TextRenderer;
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
	inputManager->RegisterCallback(this, boom, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, false, (int)OIS::KC_B);
	
}

void World::SpawnAsteroid()
{
	Asteroid *asteroid = new Asteroid(sceneManager, worldSceneNode, physicsEngine);
	float theta = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	float phi = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	Ogre::Vector3 initialPosition = Ogre::Vector3(cos(theta) * sin(phi), sin(theta) * sin(phi), -cos(phi)) * worldRadius;
	asteroid->translate(initialPosition);
	asteroidList.push_back(asteroid);
}

void World::createWorld()
{
	//TODO setup stuff for the world goes here.
}

void World::updateWorld(const Ogre::FrameEvent& fe)
{
	Entity* deadEntity = NULL;
	if (exists)
	{
		//TODO update stuff
		if (timer <= 0.0f)
		{
			SpawnAsteroid();
			timer = spawnTime;
		}
		else
		{
			timer -= fe.timeSinceLastFrame;
		}

		//first we update all of our entities in our list.
		for(std::vector<Asteroid*>::iterator it = asteroidList.begin(); it != asteroidList.end(); ++it){
			(*it)->Update(fe);

			if(!(*it)->isAlive()){
				deadEntity = (*it);
				//(*it)->explode(); //TODO PARTCILE STUFF

				//removing our now dead enetity from the list of physicsOBject
				physicsEngine.RemovePhysicsEntity((PhysicsEntity*) deadEntity);
				if (!deadEntity->isSpaghettified())
				{
					itemList.push_back(new Item(sceneManager, worldSceneNode, physicsEngine, deadEntity->getPosition(), Item::FUEL));
				}
			}
		}
		for(std::vector<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it){
			(*it)->Update(fe);
		}
		//cleanup any dead entities from those lists
		cleanupLists();
	
		//now that our lists our clean we can update the player.
		player.Update(fe);

		//Now that everything is updated we apply physics
		physicsEngine.Update(fe);
	}
}

void World::cleanupLists(bool cleanupNeeded)
{
	Entity* deadEntity;
	std::vector<Asteroid*>::iterator it = asteroidList.begin();
	while(it != asteroidList.end()){
		if((*it)->isAlive()){
			++it;
			continue;
		}

		//we need to delete if they are not alive.
		deadEntity = (*it);
		it = asteroidList.erase(it);
		if(cleanupNeeded)
			deadEntity->cleanup();
		delete deadEntity;
		deadEntity = NULL;
	}

	std::vector<Item*>::iterator iter = itemList.begin();
	while(iter != itemList.end()){
		if((*iter)->isAlive()){
			++iter;
			continue;
		}

		//we need to delete if they are not alive.
		deadEntity = (*iter);
		iter = itemList.erase(iter);
		if(cleanupNeeded)
			deadEntity->cleanup();
		delete (Item *) deadEntity;
		deadEntity = NULL;
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

	for(std::vector<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it){
		(*it)->kill();
	}

	for(std::vector<Asteroid*>::iterator it = asteroidList.begin(); it != asteroidList.end(); ++it){
		(*it)->kill();
	}

	cleanupLists(false);

	itemList.clear();
	asteroidList.clear();
}


void World::boom(void* context, const Ogre::FrameEvent& fe)
{
	if(context)
	{
		World *world = static_cast<World*>(context);
		for(std::vector<Asteroid*>::iterator it = world->asteroidList.begin(); it != world->asteroidList.end(); ++it){
			(*it)->kill();
		}
	}
}