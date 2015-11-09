#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "physics_entity.h"
#include "input_manager.h"
#include "laser.h"

class Spacecraft : public PhysicsEntity
{
public:
	Spacecraft();
	virtual ~Spacecraft() = 0;
	
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* worldNode, PhysicsEngine &physicsEngine);
	virtual void Update(const Ogre::FrameEvent &fe);

	void fireLaser();

private:
	Laser laser;
};

#endif // SPACECRAFT_H
