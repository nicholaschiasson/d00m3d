#ifndef PLAYER_SPACECRAFT_H
#define PLAYER_SPACECRAFT_H

#include <vector>
#include "spacecraft.h"
#include "weapon.h"

class PlayerSpacecraft : public Spacecraft
{
public:
	PlayerSpacecraft();
	virtual ~PlayerSpacecraft();

	virtual void cleanup(PhysicsEngine &physicsEngine);

	float getHealth();
	
	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);

	virtual void ThrustersForward();
	virtual void ThrustersLeft();
	virtual void ThrustersBackward();
	virtual void ThrustersRight();
	virtual void ThrustersUpward();
	virtual void ThrustersDownward();

	virtual PhysicsEntity *fireWeapon();
	virtual bool canNavigate();
	//testing
	void test();

	virtual Weapon *GetCurrentWeapon();
	
	virtual void SetCurrentWeapon(int weaponIndex);

private:
	std::vector<Weapon *> weapons;
	int currentWeaponIndex;

	bool thrustersAvailable();
};

#endif // PLAYER_SPACECRAFT_H
