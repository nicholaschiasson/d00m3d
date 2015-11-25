#ifndef ENEMY_SPACECRAFT_H
#define ENEMY_SPACECRAFT_H

#include "spacecraft.h"
#include "physics_engine.h"
#include "OgreSceneManager.h"
#include "sentinent_object.h"

class EnemySpacecraft : public Spacecraft, public SentinentObject
{
public:
	EnemySpacecraft();
	EnemySpacecraft(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual ~EnemySpacecraft();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
private:

};

#endif // ENEMY_SPACECRAFT_H