#include "enemy_spacecraft.h"

EnemySpacecraft::EnemySpacecraft(): physicsEngine(NULL), currState(STATE_IDLE), target(NULL), lastProjectile(NULL), lastShot(0.0), reload(2.0)
{
	materialPrefix = "Enemy";
	float random = Ogre::Math::RangeRandom(0.0f, 2.0f);
	if (random < 1.0f)
		weapon = new LaserCannon();
	else if (random >= 1.0f)
		weapon = new PlasmaCannon();

	random = Ogre::Math::RangeRandom(0.0f, 3.0f);
	if (random < 1.0f)
		type = REACTOR_CRAFT;
	else if (random >= 1.0f && random < 2.0f)
		type = SPEED_CRAFT;
	else if (random >= 2.0f && random < 3.0f)
		type = TANK_CRAFT;
}

EnemySpacecraft::EnemySpacecraft(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID):
	physicsEngine(NULL), currState(STATE_IDLE), target(NULL), lastProjectile(NULL), lastShot(0.0), reload(6.0)
{
	materialPrefix = "Enemy";
	float random = Ogre::Math::RangeRandom(0.0f, 2.0f);
	if (random < 1.0f)
		weapon = new LaserCannon();
	else if (random >= 1.0f)
		weapon = new PlasmaCannon();
	
	random = Ogre::Math::RangeRandom(0.0f, 3.0f);
	if (random < 1.0f)
		type = REACTOR_CRAFT;
	else if (random >= 1.0f && random < 2.0f)
		type = SPEED_CRAFT;
	else if (random >= 2.0f && random < 3.0f)
		type = TANK_CRAFT;

	Initialize(sceneManager, parentNode, physicsEngine, lightPos, particleEngine, parentID);
}

EnemySpacecraft::~EnemySpacecraft()
{
}

void EnemySpacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngineRef, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID){
	Spacecraft::Initialize(sceneManager, parentNode, physicsEngineRef, lightPos, particleEngine, parentID);
	physicsEngine = &physicsEngineRef;
}

void EnemySpacecraft::Update(const Ogre::FrameEvent &fe)
{
	Spacecraft::Update(fe);
	if (alive)
	{
		if(target != NULL){ //if we have a target do stuff
			switch(currState){
			case STATE_IDLE:
				handleIdle(fe);
				break;
			case STATE_PURSUE:
				handlePursue(fe);
				break;
			case STATE_TURN:
				handleTurn(fe);
				break;
			case STATE_FIRE:
				handlePursue(fe);
				handleFire(fe, false);
				break;
			case STATE_WARN:
				handlePursue(fe);
				handleFire(fe, true);
				break;
			default:
				currState = STATE_IDLE;
				break;

			}
		}
	}
}

PhysicsEntity *EnemySpacecraft::takeLastProjectile()
{
	PhysicsEntity *projectile = lastProjectile;
	lastProjectile = 0;
	return projectile;
}

void EnemySpacecraft::setTarget(Spacecraft* newTarget)
{
	target = newTarget;
}

void EnemySpacecraft::handleIdle(const Ogre::FrameEvent &fe)
{
	//need to orientate to the target.
	findTarget(fe);
	Ogre::Vector3 distance = target->getPosition() - sceneNode->getPosition();
	if(distance.squaredLength() < Ogre::Math::Sqr(1000)){
		currState = STATE_PURSUE;
	}
}

void EnemySpacecraft::handlePursue(const Ogre::FrameEvent &fe)
{
	Ogre::Vector3 distance = target->getPosition() - sceneNode->getPosition();
	//std::cout << "Distance: " <<distance.length() <<std::endl;
	if(weapon->getState() != Weapon::WEAPON_FIRING){ //ensure we dont turn as the laser is firing
		findTarget(fe);
	}
	if(distance.squaredLength() < Ogre::Math::Sqr(50)){
		if(currState == STATE_PURSUE){
			currState = STATE_WARN;
		}
		if(velocity.squaredLength() > target->GetVelocity().squaredLength()){
			ThrustersBackward();
		}
		SetLeftFlamesVisible(false);
		SetRightFlamesVisible(false);

	}else{
			ThrustersForward();
			SetLeftFlamesVisible(true);
			SetRightFlamesVisible(true);
	}
	
}

void EnemySpacecraft::handleTurn(const Ogre::FrameEvent &fe)
{
}


void EnemySpacecraft::findTarget(const Ogre::FrameEvent &fe)
{
	sceneNode->lookAt(target->getPosition(), Ogre::Node::TS_PARENT);
}

void EnemySpacecraft::handleFire(const Ogre::FrameEvent &fe, bool warningShot){
	if(lastShot + fe.timeSinceLastFrame > reload){
		lastShot = 0; 
		if(warningShot){
			Ogre::Vector3 targetUp = target->getOrientation() * Ogre::Vector3::UNIT_Y;
			targetUp.normalise(); //in case its not normalized;

			sceneNode->lookAt(target->getPosition() + targetUp, Ogre::Node::TS_PARENT);
			currState = STATE_FIRE;
		}else{
			findTarget(fe);
			currState = STATE_PURSUE;
			}
		float myEnergyLevelWillAlwaysBeHighEnoughToFireMyWeaponBecauseIAmACheatingBastard = 1000000000.0f;
		lastProjectile = fireWeapon(myEnergyLevelWillAlwaysBeHighEnoughToFireMyWeaponBecauseIAmACheatingBastard);
	}else{
		lastShot += fe.timeSinceLastFrame;
	}
	
}
