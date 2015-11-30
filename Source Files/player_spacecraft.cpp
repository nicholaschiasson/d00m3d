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
		fuelSystems.front().addValue(-0.01);
		Spacecraft::ThrustersForward();
	}
	
}
void PlayerSpacecraft::ThrustersLeft()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01);
		Spacecraft::ThrustersLeft();
	}	
}
void PlayerSpacecraft::ThrustersBackward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01);
		Spacecraft::ThrustersBackward();
	}
}
void PlayerSpacecraft::ThrustersRight()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01);
		Spacecraft::ThrustersRight();
	}
}
void PlayerSpacecraft::ThrustersUpward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01);
		Spacecraft::ThrustersUpward();
	}
}
void PlayerSpacecraft::ThrustersDownward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01);
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
		artillerySystems.front().addValue(-0.01f);
	}
}

bool PlayerSpacecraft::canNavigate()
{
	return navigationalSystems.size() > 0;
}