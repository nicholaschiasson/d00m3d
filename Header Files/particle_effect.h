#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include "physics_entity.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreManualObject.h"
#include "OgreEntity.h"
#include "OgreFrameListener.h"
#include "physics_engine.h"

class ParticleEffect: public PhysicsEntity{
public:
	ParticleEffect(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine);

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name,PhysicsEngine &physicsEngine, unsigned int parentID = -1);
	void Update(const Ogre::FrameEvent& fe);
	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);
private:
	void CreateParticleEntity(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String entity_name, Ogre::String object_name, Ogre::String material_name); // Create an entity of an object
	float timer;
	float duration;
	std::string materialName;
};

#endif //PARTICLE_EFFECT_H