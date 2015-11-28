#ifndef LASER_H
#define LASER_H

#include "physics_entity.h"
#include <OgreEntity.h>

class Laser: public PhysicsEntity
{
public:
	Laser();
	~Laser();

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);

	void fire();
	void cooldown();
	void upgrade(int dmg);

	int getDamage() const;	

private:
	int damage;

};

#endif //LASER_H