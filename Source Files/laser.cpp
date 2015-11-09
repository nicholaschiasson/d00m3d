#include "laser.h"

Laser::Laser(): cooldown(5), duration(5), timer(0), damage(1), active(false), myState(LASER_READY)
{
	//lalala
}

Laser::~Laser()
{
}

int Laser::getDamage() const
{
	return damage;
}

int Laser::getCooldown() const
{
	return cooldown;
}

void Laser::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode)
{
	//setting our mass to 0
	mass = 0.0;
	sceneNode = parentNode->createChildSceneNode("Laser");

	Ogre::Entity *laserEntity = sceneManager->createEntity("Cylinder");
	laserEntity->setMaterialName("LaserMaterial");
	sceneNode->attachObject(laserEntity);
	sceneNode->scale(0.05f, 100.0f, 0.05f);
	sceneNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	sceneNode->translate(0,50.5,-.5, Ogre::Node::TS_LOCAL);

	sceneNode->setVisible(false);
}

void Laser::upgrade(int maxCooldown, int dmg)
{
	cooldown = maxCooldown;
	damage = dmg;
}

Laser::LASER_STATE Laser::getState()
{
	return myState;
}

void Laser::fire()
{
	if(myState == LASER_READY){
		myState = LASER_FIRING;
		timer = duration;
		sceneNode->setVisible(true);
	}
}

void Laser::update()
{
	PhysicsEntity::update();
	if(alive){
		if(timer == 0){
			switch(myState){
			case LASER_COOLDOWN:
				myState = LASER_READY;
				break;
			case LASER_FIRING:
				sceneNode->setVisible(false);
				myState = LASER_COOLDOWN;
				timer = cooldown;
				break;
			}
		}
		else{
			timer--;
		}
	}
}