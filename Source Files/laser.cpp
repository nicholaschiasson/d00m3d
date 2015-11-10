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

void Laser::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine);

	//setting our mass to 0
	dynamic = false;
	mass = 0.0;

	Ogre::Entity *laserEntity = sceneManager->createEntity("Cylinder");
	laserEntity->setMaterialName("LaserMaterial");
	Ogre::SceneNode *laserSceneNode = sceneNode->createChildSceneNode("Laser" + Ogre::StringConverter::toString(entityCount));
	laserSceneNode->attachObject(laserEntity);
	laserSceneNode->scale(0.05f, 100.0f, 0.05f);
	laserSceneNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	laserSceneNode->translate(0,50.5,-.5, Ogre::Node::TS_LOCAL);

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

void Laser::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);
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