#include "player_spacecraft.h"

PlayerSpacecraft::PlayerSpacecraft()
{
}

PlayerSpacecraft::~PlayerSpacecraft()
{
}


float PlayerSpacecraft::getHealth(){

	return health;
}
void PlayerSpacecraft::Update(const Ogre::FrameEvent &fe)
{
	Spacecraft::Update(fe);
	//todo temporary
	//std::cout << "Health: " << health << std::endl;

}