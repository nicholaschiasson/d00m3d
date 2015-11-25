#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include "enemy_spacecraft.h"
#include "physics_engine.h"
#include <vector>

class aiManager{
public:
	aiManager();
	~aiManager();
	//passes in a physicsEngine* to add ships to it, keeps a reference to physicsEngine, does not clean up the physicsEngine
	void initialize(Ogre::SceneManager *sceneManagerRef, Ogre::SceneNode *parentNodeRef, PhysicsEngine *physicsEngineRef);
	void trainNewShip(Ogre::Vector3 position);
private:
	std::vector<EnemySpacecraft*> fleet;
	PhysicsEngine* physicsEngine;
	Ogre::SceneManager* sceneManager;
	Ogre::SceneNode*	parentNode;

};

#endif //AI_MANAGER_H