#ifndef WEAPON_H
#define WEAPON_H

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "physics_entity.h"
#include "particle_engine.h"

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

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::SceneNode *world, PhysicsEngine &physicsEngine, ParticleEngine *particleEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe, Ogre::Vector3 velocity);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
	virtual PhysicsEntity *fire() = 0;
	virtual void upgrade(int maxCooldown, int dmg) = 0;
	
	int getCooldown() const;
	WEAPON_STATE getState();
	float getEnergyRequirement() const;

protected:
	Ogre::String materialPrefix;
	Ogre::SceneNode *barrel;
	int timer;
	int cooldown;
	Ogre::Vector3 relativeVelocity;
	WEAPON_STATE myState;
	float energyRequirement;

	Ogre::SceneManager *sceneManager;
	Ogre::SceneNode *worldNode;
	PhysicsEngine *physicsEngine;
	ParticleEngine *particleEngine;
	
};

#endif // WEAPON_H