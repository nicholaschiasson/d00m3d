#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include "enemy_spacecraft.h"
#include "physics_engine.h"
#include <vector>

class aiManager{
public:
	aiManager(PhysicsEngine* physicsEngineRef);
	aiManager();
	~aiManager();
	//passes in a physicsEngine* to add ships to it, keeps a reference to physicsEngine, does not clean up the physicsEngine
	initialize(PhysicsEngine* physicsEngineRef);
	trainNewShip(Ogre::Vector3 position);
private:
	std::vector<EnemySpacecraft*> fleet;
	PhysicsEngine* physicsEngine

};

#endif //AI_MANAGER_H