#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

class ParticleEffect{
public:
	ParticleEffect(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String entity_name, Ogre::String object_name, Ogre::String material_name, Ogre::Vector3 position);

private:
	float timer;
	float duration;
}

#endif //PARTICLE_EFFECT_H