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
		return false;
	}
	if(fuelSystems.front().getValue() <= 0){
		return false;
	}
	return true;
}

void PlayerSpacecraft::test(){
	if(navigationalSystems.size() > 0)
		navigationalSystems.front().setHealth(0);
}

void PlayerSpacecraft::fireLaser()
{
	if(artillerySystems.size() > 0 && artillerySystems.front().getValue() > 0){
		Spacecraft::fireLaser();
	}
}

bool PlayerSpacecraft::canNavigate()
{
	return navigationalSystems.size() > 0;
}