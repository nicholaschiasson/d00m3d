#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "physics_entity.h"
#include "input_manager.h"

class Spacecraft : public PhysicsEntity
{
public:
	Spacecraft();
	virtual ~Spacecraft() = 0;

	virtual void Initialize(Ogre::SceneManager *sceneManager);

private:

};

#endif // SPACECRAFT_H
