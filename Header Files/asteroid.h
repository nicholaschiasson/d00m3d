#ifndef ASTEROID_H
#define ASTEROID_H

#include "physics_entity.h"
#include "input_manager.h"

class Asteroid : public PhysicsEntity
{
public:
	Asteroid();
	virtual ~Asteroid();
    virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *worldNode);
	virtual void Initialize(Ogre::SceneManager *sceneManager,Ogre::SceneNode *worldNode, std::string);
	Ogre::SceneNode* getAsteroidSceneNode();
	Ogre::Vector3 pos; // Position
	
private:
        Ogre::Quaternion ori; // Orientation
        Ogre::Quaternion lm; // Angular momentum (use as velocity)
		Ogre::Vector3 drift; // Drift direction
		std::string name;
};

#endif // ASTEROID_H
