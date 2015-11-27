#ifndef ENEMY_SPACECRAFT_H
#define ENEMY_SPACECRAFT_H

#include "spacecraft.h"
#include "physics_engine.h"
#include "OgreSceneManager.h"
#include "OgreQuaternion.h"

class EnemySpacecraft : public Spacecraft
{
public:
	EnemySpacecraft();
	EnemySpacecraft(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);

	enum mindState{
		STATE_IDLE,
		STATE_PURSUE,
		STATE_TURN,
		STATE_FIRE,
		STATE_WARN
	};

	virtual ~EnemySpacecraft();
	virtual void setTarget(Spacecraft* newTarget);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
private:
	PhysicsEngine *physicsEngine;
	mindState currState;
	Spacecraft* target;
	float lastShot;
	float reload;

	void handleIdle(const Ogre::FrameEvent &fe);
	void handlePursue(const Ogre::FrameEvent &fe);
	void handleTurn(const Ogre::FrameEvent &fe);
	void handleFire(const Ogre::FrameEvent &fe, bool warningShot);
	void findTarget(const Ogre::FrameEvent &fe);

};

#endif // ENEMY_SPACECRAFT_H