#include "laser.h"

Laser::Laser(): cooldown(5), duration(5), timer(0), damage(100), active(false), myState(LASER_READY)
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

void Laser::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	//setting our mass to 0
	bodyType = ENTITY_BODY_METAPHYSICAL;
	dynamic = false;
	mass = 0.0;

	Ogre::Entity *laserEntity = sceneManager->createEntity("Cylinder");
	laserEntity->setMaterialName("LaserMaterial");
	Ogre::SceneNode *laserSceneNode = sceneNode->createChildSceneNode("Laser" + Ogre::StringConverter::toString(entityCount));
	laserSceneNode->attachObject(laserEntity);
	laserSceneNode->scale(0.05f, 100.0f, 0.05f);
	laserSceneNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	laserSceneNode->translate(0,0,-50.5f);

	sceneNode->setVisible(false);
}

void Laser::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	physicsEntity->Damage(damage * fe.timeSinceLastFrame);
}

void Laser::Damage(float damage)
{
	// nope
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
		bodyType = ENTITY_BODY_METAPHYSICAL_RAY;
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
				bodyType = ENTITY_BODY_METAPHYSICAL;
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