#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreManualObject.h"
#include "OgreEntity.h"
#include "OgreFrameListener.h"
#include <vector>

#include "particle_effect.h"

class ParticleEngine{
public:
	ParticleEngine();
	~ParticleEngine();
	enum EFFECT_TYPE{
		EFFECT_EXPLOSION
	};
	void initialize(Ogre::SceneManager* scene_manager, PhysicsEngine& physics_engine);
	
	void createParticleEffect(EFFECT_TYPE effect, Ogre::SceneNode* parentNode, Ogre::Vector3 position, Ogre::Vector3 scale);
	void update(const Ogre::FrameEvent& fe);
	
private:
	std::vector<ParticleEffect*> particles;
	PhysicsEngine* physicsEngine;
	Ogre::SceneManager* sceneManager;
	
	void createExplosionGeometry(int numParticles = 3000);
	void cleanupParticles();
};

#endif //PARTICLE_ENGINE_H
