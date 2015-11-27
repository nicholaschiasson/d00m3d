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
	
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);

	virtual void spaghettify();

	void fireLaser();

	void ThrustersForward();
	void ThrustersLeft();
	void ThrustersBackward();
	void ThrustersRight();
	void ThrustersUpward();
	void ThrustersDownward();

protected:
	Laser laser;
	float thrusterForce;
};

#endif // SPACECRAFT_H
