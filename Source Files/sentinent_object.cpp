#include "sentinent_object.h"

SentinentObject::SentinentObject(): physicsEngine(NULL), target(NULL)
{
}
SentinentObject::~SentinentObject()
{
}

void SentinentObject::Initialize(PhysicsEngine& physicsEngineRef)
{
	physicsEngine = &physicsEngineRef;
}
void SentinentObject::Update(const Ogre::FrameEvent &fe)
{
}