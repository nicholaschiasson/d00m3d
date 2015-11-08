//world.cpp

#include "world.h"


World::World(): worldSceneNode(NULL), camera(NULL), sceneManager(NULL), inputManager(NULL)
{
	//lattahdah lattahdah
}

World::~World()
{
	//TODO memory cleanup
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
	camera = cam;
	inputManager = inMan;

	//creating the player entitty
	player.Initialize(sceneManager);
	camera->attachTo(player.getSceneNode());
	
	//Setting up the basic control scheme
	initControls();
}

/*
* Setting up the Controls
*/

void World::initControls()
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
}

void World::setupAsteroids()
{
}

/*
* InputManger Callbacks
*/

void World::PlayerMoveForward(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cDirection = myCamera->getDirection();

		myCameraNode->translate(cDirection * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerMoveLeft(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cRight = myCamera->getRight();
		
		myCameraNode->translate(-cRight * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerMoveBackward(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cDirection = myCamera->getDirection();

		myCameraNode->translate(-cDirection * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerMoveRight(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cRight = myCamera->getRight();
		
		myCameraNode->translate(cRight * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerMoveUp(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cUp = myCamera->getUp();
		
		myCameraNode->translate(cUp * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerMoveDown(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");
		Ogre::Vector3 cUp = myCamera->getUp();
		
		myCameraNode->translate(-cUp * fe.timeSinceLastFrame);
	*/}
}

void World::PlayerPitchUp(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");

		myCamera->pitch(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	*/}
}

void World::PlayerYawLeft(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");

		myCamera->yaw(Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	*/}
}

void World::PlayerPitchDown(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");

		myCamera->pitch(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	*/}
}

void World::PlayerYawRight(void *context, const Ogre::FrameEvent& fe)
{
	if (context)
	{/*
		PlayerSpacecraft *player = static_cast<PlayerSpacecraft *>(context);
		
		Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();
		Ogre::Node *myCameraNode = (Ogre::SceneNode *)root_scene_node->getChild("MyCameraNode");
		Ogre::Player *myCamera = scene_manager->getCamera("MyCamera");

		myCamera->yaw(-Ogre::Radian((Ogre::Math::PI / 4) * fe.timeSinceLastFrame));
	*/}
}