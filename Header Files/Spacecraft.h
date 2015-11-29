#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <list>
#include <OgreVector3.h>
#include "physics_entity.h"
#include "input_manager.h"
#include "black_hole_cannon.h"
#include "laser_cannon.h"
#include "plasma_cannon.h"
#include "system_component.h"

class Spacecraft : public PhysicsEntity
{
public:
	Spacecraft();
	virtual ~Spacecraft() = 0;
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);

	virtual void spaghettify();

	void fireLaser();
	
	float getDefense();
	float getEnergy();
	float getFuel();
	float getSpeed(); //returns the velocitySquared (to save on computation)

	SystemComponent* getActiveSystem(SystemComponent::SYSTEM_TYPE);
	int getNumSystemBackups(SystemComponent::SYSTEM_TYPE);

	void ThrustersForward();
	void ThrustersLeft();
	void ThrustersBackward();
	void ThrustersRight();
	void ThrustersUpward();
	void ThrustersDownward();

	virtual void Damage(float damage);

protected:
	Ogre::String materialPrefix;
	Ogre::Vector3 light;
	Ogre::SceneNode *leftPanelPivot;
	Ogre::SceneNode *rightPanelPivot;
	float thrusterForce;
	std::list<SystemComponent> artillerySystems;
	std::list<SystemComponent> defenseSystems;
	std::list<SystemComponent> fuelSystems;
	std::list<SystemComponent> navigationalSystems;
	Weapon *weapon;
};

#endif // SPACECRAFT_H
