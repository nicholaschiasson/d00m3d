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

void PlayerSpacecraft::ThrustersForward()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersForward();
	}
	
}
void PlayerSpacecraft::ThrustersLeft()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersLeft();
	}	
}
void PlayerSpacecraft::ThrustersBackward()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersBackward();
	}
}
void PlayerSpacecraft::ThrustersRight()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersRight();
	}
}
void PlayerSpacecraft::ThrustersUpward()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersUpward();
	}
}
void PlayerSpacecraft::ThrustersDownward()
{
	if(thrustersAvailable()){
		Spacecraft::ThrustersDownward();
	}
}

bool PlayerSpacecraft::thrustersAvailable(){
	if(fuelSystems.size() <= 0){
		std::cout << "No Thrusters alive"<< std::endl;
		return false;
	}
	if(fuelSystems.front().getValue() <= 0){
		std::cout << "Thrusters empty"<< std::endl;
		return false;
	}
	return true;
}

void PlayerSpacecraft::test(){
	fuelSystems.front().setHealth(0);
}