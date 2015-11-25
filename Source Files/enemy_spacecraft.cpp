#include "enemy_spacecraft.h"

EnemySpacecraft::EnemySpacecraft()
{
}

EnemySpacecraft::EnemySpacecraft(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	Initialize(sceneManager, parentNode, physicsEngine, parentID);
}

EnemySpacecraft::~EnemySpacecraft()
{
}

void EnemySpacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, unsigned int parentID){
	Spacecraft::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	SentinentObject::Initialize(physicsEngine);
}

void EnemySpacecraft::Update(const Ogre::FrameEvent &fe)
{
	Spacecraft::Update(fe);
	SentinentObject::Update(fe);
}