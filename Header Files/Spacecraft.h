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
	enum SPACECRAFT_TYPE
	{
		REACTOR_CRAFT,
		SPEED_CRAFT,
		TANK_CRAFT,
	};

	Spacecraft();
	virtual ~Spacecraft() = 0;
	virtual void cleanup(PhysicsEngine &physicsEngine);
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity);

	virtual PhysicsEntity *fireWeapon(float &energy);
	
	float getDefense();
	float getEnergy();
	float getFuel();

	SystemComponent* getActiveSystem(SystemComponent::SYSTEM_TYPE);
	int getNumSystemBackups(SystemComponent::SYSTEM_TYPE);

	virtual void ThrustersForward();
	virtual void ThrustersLeft();
	virtual void ThrustersBackward();
	virtual void ThrustersRight();
	virtual void ThrustersUpward();
	virtual void ThrustersDownward();

	virtual void Damage(float damage);

protected:
	Ogre::String materialPrefix;
	SPACECRAFT_TYPE type;
	Ogre::Vector3 light;
	Ogre::SceneNode *leftPanelPivot;
	Ogre::SceneNode *rightPanelPivot;
	Ogre::SceneNode *antennaPivot;
	Ogre::SceneNode *hoverShield;
	float thrusterForce;
	std::list<SystemComponent> artillerySystems;
	std::list<SystemComponent> defenseSystems;
	std::list<SystemComponent> fuelSystems;
	std::list<SystemComponent> navigationalSystems;
	Ogre::SceneNode *weaponArm;
	Weapon *weapon;
};

#endif // SPACECRAFT_H
