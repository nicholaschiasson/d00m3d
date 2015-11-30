#ifndef WEAPON_H
#define WEAPON_H

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "physics_entity.h"

class Weapon : public PhysicsEntity
{
public:
	Weapon();
	~Weapon() = 0;

	enum WEAPON_STATE{
		WEAPON_COOLDOWN,
		WEAPON_READY,
		WEAPON_FIRING
	};

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual void fire() = 0;
	virtual void upgrade(int maxCooldown, int dmg) = 0;
	
	int getCooldown() const;
	WEAPON_STATE getState();

protected:
	Ogre::String materialPrefix;
	Ogre::SceneNode *barrel;
	int timer;
	int cooldown;
	WEAPON_STATE myState;
	
};

#endif // WEAPON_H