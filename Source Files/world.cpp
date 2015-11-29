//world.cpp

#include "world.h"

World::World(): worldSceneNode(NULL), camera(NULL), sceneManager(NULL)
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
	sceneManager->setSkyBox(true, "SkyboxMaterial");

	health.InitOverlay(sceneMan);

	worldSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode("_worldSceneNode_");
	camera = cam;

	exists = true;
	spawnTime = 2.0f;
	timer = spawnTime;

	numObjects = 0;
	//tr = new TextRenderer;


	//setting up the PartcileEffectGeometry
	particleEngine.initialize(sceneManager, physicsEngine);

	star.Initialize(sceneManager, worldSceneNode, physicsEngine);
	//todo replace with actual star co-ordinates
	star.pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	star.translate(5000,5000,5000);

	//creating the player entity
	player.Initialize(sceneManager, worldSceneNode, physicsEngine, star.getPosition());
	camera->attachTo(&player);
	
	//initObjects();
	//Setting up the basic control scheme
	initControls(inMan);
	createWorld();
}

/*
* Setting up the Controls
*/

void World::initControls(InputManager *inputManager)
{
	inputManager->RegisterCallback(this, PlayerMoveForward, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_W);
	inputManager->RegisterCallback(this, PlayerMoveLeft, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_A);
	inputManager->RegisterCallback(this, PlayerMoveBackward, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_S);
	inputManager->RegisterCallback(this, PlayerMoveRight, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_D);
	inputManager->RegisterCallback(this, PlayerMoveUp, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_Q);
	inputManager->RegisterCallback(this, PlayerMoveDown, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_C);
	inputManager->RegisterCallback(this, PlayerPitchUp, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_UP);
	inputManager->RegisterCallback(this, PlayerYawLeft, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_LEFT);
	inputManager->RegisterCallback(this, PlayerPitchDown, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_DOWN);
	inputManager->RegisterCallback(this, PlayerYawRight, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_RIGHT);
	inputManager->RegisterCallback(this, playerFireLaser, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_SPACE);
	inputManager->RegisterCallback(this, boom, INPUT_SOURCE_KEYBOARD, INPUT_EVENT_HOLD, MOUSE_MOTION_STATE_EITHER, (int)OIS::KC_B);
	inputManager->RegisterCallback(this, PlayerRotate, INPUT_SOURCE_NONE, INPUT_EVENT_NONE, MOUSE_MOTION_STATE_MOVING, 0);
	
}

void World::SpawnAsteroid(Ogre::Vector3 pos)
{
	
	Asteroid *asteroid = new Asteroid(sceneManager, worldSceneNode, physicsEngine);
	float theta = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	float phi = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
	Ogre::Vector3 initialPosition = pos + Ogre::Vector3(cos(theta) * sin(phi),sin(theta) * sin(phi), -cos(phi)) * 3000.0f;
	asteroid->translate(initialPosition);
	asteroidList.push_back(asteroid);
	numObjects++;
}
void World::checkDistance(Entity* entity){
	Ogre::Vector3 distance = entity->getPosition() - player.getPosition(); 
	if(distance.squaredLength() > Ogre::Math::Sqr(4000)){
		entity->kill(); 

	}

}

void World::initObjects(){
	Ogre::Vector3 pos = player.getPosition();
	for (int i = 0; i<80; i++){
		Asteroid *asteroid = new Asteroid(sceneManager, worldSceneNode, physicsEngine);
		float theta = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
		float phi = Ogre::Math::RangeRandom(0.0f, Ogre::Math::TWO_PI);
		float dist = Ogre::Math::RangeRandom(500.0,3000.0);
		Ogre::Vector3 initialPosition = pos + Ogre::Vector3(cos(theta) * sin(phi),sin(theta) * sin(phi), -cos(phi)) * dist;
		asteroid->translate(initialPosition);
		asteroidList.push_back(asteroid);
		numObjects++;
	}
}
void World::createWorld()
{
	//TODO setup stuff for the world goes here.
	setupEnemies();
}

void World::updateWorld(const Ogre::FrameEvent& fe)
{
	//std::cout << numObjects << std::endl;
	Entity* deadEntity = NULL;

	if (exists)
	{
		//TODO update stuff
		if (timer <= 0.0f)
		{
			for(int i = 0; i<20; i++){
				if(numObjects < MAX_NUM_OBJECTS){
				    //SpawnAsteroid(player.getPosition());
				}
			}
			timer = spawnTime;
		}
		else
		{
			timer -= fe.timeSinceLastFrame;
		}

		//first we update all of our entities in our list.

		//star.roll(Ogre::Radian(-Ogre::Degree(2.0f * fe.timeSinceLastFrame)));

		//enemy spacecraft list
		for(std::vector<EnemySpacecraft*>::iterator it = fleet.begin(); it != fleet.end(); ++it){
			//checkDistance(*it); todo determine if enemies should be deleted
			(*it)->Update(fe);

			if(!(*it)->isAlive()){
				deadEntity = (*it);
				particleEngine.createParticleEffect(ParticleEngine::EFFECT_EXPLOSION, worldSceneNode, (*it)->getPosition(), Ogre::Vector3(1,1,1));
				itemList.push_back(new Item(sceneManager, worldSceneNode, physicsEngine, deadEntity->getPosition(), Resource::FUEL));
			}
		}

		//asteroid list
		for(std::vector<Asteroid*>::iterator it = asteroidList.begin(); it != asteroidList.end(); ++it){
			(*it)->Update(fe);

			if(!(*it)->isAlive()){
				deadEntity = (*it);
				particleEngine.createParticleEffect(ParticleEngine::EFFECT_EXPLOSION, worldSceneNode, (*it)->getPosition(), Ogre::Vector3(1,1,1));
				itemList.push_back(new Item(sceneManager, worldSceneNode, physicsEngine, deadEntity->getPosition(), Resource::FUEL));

			}
			checkDistance(*it);
		}

		//itemlist
		for(std::vector<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it){
			(*it)->Update(fe);

			if(!(*it)->isAlive()){
				deadEntity = (*it);
				//(*it)->explode(); //TODO PARTCILE STUFF
				
			}
			checkDistance(*it);
		}
		//cleanup any dead entities from those lists
		cleanupLists(true);
	
		//now that our lists our clean we can update the player.
		player.Update(fe);
		if(!player.isAlive()){
			//std::cout << "YOU DIED! GAME OVER" <<std::endl;
		}

		//Now that everything is updated we apply physics
		physicsEngine.Update(fe);
		particleEngine.update(fe);
	}
}

void World::cleanupLists(bool cleanupNeeded)
{
	PhysicsEntity* deadEntity;

	//enemyspacecraft cleanup
	std::vector<EnemySpacecraft*>::iterator i = fleet.begin();
	while(i != fleet.end()){
		if((*i)->isAlive()){
			++i;
			continue;
		}

		//we need to delete if they are not alive.
		deadEntity = (*i);
		i = fleet.erase(i);
		if(cleanupNeeded)
			deadEntity->cleanup(physicsEngine);
		delete deadEntity;
		deadEntity = NULL;
	}

	//asteroid cleanup
	std::vector<Asteroid*>::iterator it = asteroidList.begin();
	while(it != asteroidList.end()){
		if((*it)->isAlive()){
			++it;
			continue;
		}
		numObjects--;

		//we need to delete if they are not alive.
		deadEntity = (*it);
		it = asteroidList.erase(it);
		if(cleanupNeeded)
			deadEntity->cleanup(physicsEngine);

		delete deadEntity;
		deadEntity = NULL;
	}

	//item cleanup
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
			deadEntity->cleanup(physicsEngine);
		delete (Item *) deadEntity;
		deadEntity = NULL;
	}
}

/*
* InputManger Callbacks
*/

void World::PlayerMoveForward(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World *>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersForward();
	}
}

void World::PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersLeft();
	}
}

void World::PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersBackward();
	}
}

void World::PlayerMoveRight(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersRight();
	}
}

void World::PlayerMoveUp(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersUpward();
	}
}

void World::PlayerMoveDown(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;
		player->ThrustersDownward();
	}
}

void World::PlayerPitchUp(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->pitch(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerYawLeft(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->yaw(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerPitchDown(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->pitch(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::PlayerYawRight(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->yaw(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	}
}

void World::playerFireLaser(void* context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
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

	for(std::vector<EnemySpacecraft*>::iterator it = fleet.begin(); it != fleet.end(); ++it){
		(*it)->kill();
	}
	cleanupLists(false);

	itemList.clear();
	asteroidList.clear();
	fleet.clear();
}


void World::boom(void* context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if(context)
	{
		World *world = static_cast<World*>(context);
		for(std::vector<Asteroid*>::iterator it = world->asteroidList.begin(); it != world->asteroidList.end(); ++it){
			(*it)->kill();
		}
	}
}

void World::PlayerRotate(void *context, const Ogre::FrameEvent& fe, int x1, int y1, int z1, int x2, int y2, int z2)
{
	if(context)
	{
		World *world = static_cast<World*>(context);
		PlayerSpacecraft *player = &world->player;

		player->pitch(Ogre::Radian(Ogre::Degree(-(float)(y2 - y1))) * fe.timeSinceLastFrame);
		player->yaw(Ogre::Radian(Ogre::Degree(-(float)(x2 - x1))) * fe.timeSinceLastFrame);
	}
}

void World::setupEnemies()
{
	EnemySpacecraft* recruit = new EnemySpacecraft(sceneManager, worldSceneNode, physicsEngine, star.getPosition());
	recruit->translate(player.getPosition() + Ogre::Vector3(0,0,-75));
	recruit->setTarget(&player);
	fleet.push_back(recruit);

	//TODO: Add more enemies.
}