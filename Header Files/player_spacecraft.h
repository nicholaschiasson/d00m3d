#ifndef PLAYER_SPACECRAFT_H
#define PLAYER_SPACECRAFT_H

#include "spacecraft.h"

class PlayerSpacecraft : public Spacecraft
{
public:
	PlayerSpacecraft();
	virtual ~PlayerSpacecraft();

	float getHealth();
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
	

private:
	bool thrustersAvailable();
};

#endif // PLAYER_SPACECRAFT_H
