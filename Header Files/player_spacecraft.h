#ifndef PLAYER_SPACECRAFT_H
#define PLAYER_SPACECRAFT_H

#include "spacecraft.h"

class PlayerSpacecraft : public Spacecraft
{
public:
	PlayerSpacecraft();
	virtual ~PlayerSpacecraft();
	virtual void Update(const Ogre::FrameEvent &fe);

private:

};

#endif // PLAYER_SPACECRAFT_H
