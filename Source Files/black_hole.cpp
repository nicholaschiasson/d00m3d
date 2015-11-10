#include "black_hole.h"

#include "OgreEntity.h"

BlackHole::BlackHole()
{
}

BlackHole::~BlackHole()
{
}

void BlackHole::Initialize(Ogre::SceneManager* sceneManager, Ogre::SceneNode *worldNode){
	Ogre::Entity *bhEntity = sceneManager->createEntity("Sphere");
	Ogre::SceneNode *rootSceneNode = sceneManager->getRootSceneNode();
	bhEntity->setMaterialName("BlackHoleMaterial");
	sceneNode = worldNode->createChildSceneNode("BlackHole");
	sceneNode->attachObject(bhEntity);
	size = 10.0f;
	sceneNode->setScale(size,size,size);
}

Ogre::SceneNode* BlackHole::getSceneNode(){

	return sceneNode;
}

float BlackHole::getSize(){
	return size;
}