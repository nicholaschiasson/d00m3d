#ifndef SENTINENT_H
#define SENTINENT_H

#include "enemy_spacecraft.h"
#include "physics_engine.h"

class SentinentObject{
public:
	SentinentObject();
	~SentinentObject();
	//passes in a physicsEngine* to add ships to it, keeps a reference to physicsEngine, does not clean up the physicsEngine
	virtual void initialize(PhysicsEngine *physicsEngineRef);

	virtual void update(const Ogre::FrameEvent &fe) =0;
private:
	PhysicsEngine *physicsEngine;
	Spacecraft* target;
};

#endif //SENTINENT_H