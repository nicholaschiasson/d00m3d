#include "player_spacecraft.h"

PlayerSpacecraft::PlayerSpacecraft() : currentWeaponIndex(0)
{
	weapons.push_back(new LaserCannon());
	weapons.push_back(new PlasmaCannon());
	weapons.push_back(new BlackHoleCannon());
	weapon = weapons[0];
}

PlayerSpacecraft::~PlayerSpacecraft()
{
}

void PlayerSpacecraft::cleanup(PhysicsEngine &physicsEngine)
{
	if (weapons.size() > 0)
	{
		for (std::vector<Weapon *>::iterator it = ++weapons.begin(); it != weapons.end(); ++it)
		{
			(*it)->detachFrom(physicsEngine);
		}
	}
	Spacecraft::cleanup(physicsEngine);
}

float PlayerSpacecraft::getHealth(){
	
	return health;
}

void PlayerSpacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID)
{
	Spacecraft::Initialize(sceneManager, parentNode, physicsEngine, lightPos, particleEngine, parentID);

	unsigned int pid = (parentID == -1 ? objectID : parentID);
	
	if (weapons.size() > 0)
	{
		for (std::vector<Weapon *>::iterator it = ++weapons.begin(); it != weapons.end(); ++it)
		{
			if (*it != 0)
			{
				(*it)->Initialize(sceneManager, weaponArm, parentNode, physicsEngine, particleEngine, pid);
				(*it)->scale(1.0f / 0.1f, 1.0f / 0.2f, 1.0f / 0.1f);
				(*it)->translate(0.0f, -0.9f, 0.0f);
				(*it)->setVisible(false);
			}
		}
	}
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
		fuelSystems.front().addValue(-0.01f);
		Spacecraft::ThrustersForward();
	}
	
}
void PlayerSpacecraft::ThrustersLeft()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01f);
		Spacecraft::ThrustersLeft();
	}	
}
void PlayerSpacecraft::ThrustersBackward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01f);
		Spacecraft::ThrustersBackward();
	}
}
void PlayerSpacecraft::ThrustersRight()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01f);
		Spacecraft::ThrustersRight();
	}
}
void PlayerSpacecraft::ThrustersUpward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01f);
		Spacecraft::ThrustersUpward();
	}
}
void PlayerSpacecraft::ThrustersDownward()
{
	if(thrustersAvailable()){
		fuelSystems.front().addValue(-0.01f);
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

PhysicsEntity *PlayerSpacecraft::fireWeapon()
{
	if(artillerySystems.size() > 0 && artillerySystems.front().getValue() > 0){
		artillerySystems.front().addValue(-0.01f);
		return Spacecraft::fireWeapon();
	}
	return 0;
}

bool PlayerSpacecraft::canNavigate()
{
	return navigationalSystems.size() > 0;
}

Weapon *PlayerSpacecraft::GetCurrentWeapon()
{
	return weapons[currentWeaponIndex];
}

void PlayerSpacecraft::SetCurrentWeapon(int weaponIndex)
{
	if (weaponIndex >= 0 && weaponIndex < (int)weapons.size())
	{
		weapon->setVisible(false);
		weapon = weapons[weaponIndex];
		weapon->setVisible(true);
		currentWeaponIndex = weaponIndex;
	}
}