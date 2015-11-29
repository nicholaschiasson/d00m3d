#ifndef PLAYER_SPACECRAFT_H
#define PLAYER_SPACECRAFT_H

#include "spacecraft.h"

class PlayerSpacecraft : public Spacecraft
{
public:
	PlayerSpacecraft();
	virtual ~PlayerSpacecraft();
	float getHealth();
private:

};

#endif // PLAYER_SPACECRAFT_H
