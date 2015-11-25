#ifndef SENTINENT_H
#define SENTINENT_H

#include "physics_engine.h"
#include "Spacecraft.h"

class SentinentObject{
public:
	enum mindState{
		STATE_IDLE,
		STATE_PURSUE,
		STATE_TURN,
	};
	SentinentObject();
	virtual ~SentinentObject() =0;
	//passes in a physicsEngine* to add ships to it, keeps a reference to physicsEngine, does not clean up the physicsEngine
	virtual void Initialize(PhysicsEngine& physicsEngineRef);

	virtual void Update(const Ogre::FrameEvent &fe);
private:
	PhysicsEngine *physicsEngine;
	Spacecraft* target;
	mindState currState;
};

#endif //SENTINENT_H