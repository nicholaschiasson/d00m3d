#include "enemy_spacecraft.h"

EnemySpacecraft::EnemySpacecraft(): physicsEngine(NULL), currState(STATE_IDLE), target(NULL), thrusterCount(0)
{
}

EnemySpacecraft::EnemySpacecraft(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID):
	physicsEngine(NULL), currState(STATE_IDLE), target(NULL), thrusterCount(0)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}

EnemySpacecraft::~EnemySpacecraft()
{
}

void EnemySpacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngineRef, unsigned int parentID){
	Spacecraft::Initialize(sceneManager, parentNode, physicsEngineRef, parentID);
	physicsEngine = &physicsEngineRef;
}

void EnemySpacecraft::Update(const Ogre::FrameEvent &fe)
{
	Spacecraft::Update(fe);
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
		default:
			break;

		}
	}
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
	std::cout << "Distance: " <<distance.length() <<std::endl;
	if(distance.length() < 50){
		currState = STATE_PURSUE;
	}
}

void EnemySpacecraft::handlePursue(const Ogre::FrameEvent &fe)
{
	Ogre::Vector3 distance = target->getPosition() - sceneNode->getPosition();
	std::cout << "Distance: " <<distance.length() <<std::endl;
	findTarget(fe);
	if(distance.length() < 10){
		if(velocity.length() > target->GetVelocity().length()){
			std::cout << "Speed: " << velocity.length() << std::endl;
			ThrustersBackward();
		}

	}else{
		ThrustersForward();
		thrusterCount++;
	}
	
}

void EnemySpacecraft::handleTurn(const Ogre::FrameEvent &fe)
{
}


void EnemySpacecraft::findTarget(const Ogre::FrameEvent &fe)
{
	sceneNode->lookAt(target->getPosition(), Ogre::Node::TS_PARENT);
}
