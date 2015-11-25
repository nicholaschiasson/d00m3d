#include "ai_manager.h"

aiManager::aiManager(): sceneManager(NULL), parentNode(NULL)
{
}

aiManager::~aiManager()
{
}

void aiManager::initialize(Ogre::SceneManager *sceneManagerRef, Ogre::SceneNode *parentNodeRef, PhysicsEngine *physicsEngineRef)
{
	if(sceneManagerRef == NULL || parentNodeRef == NULL){
		throw std::runtime_error("Passed in a NULL Reference");
		return;
	}

	sceneManager = sceneManagerRef;
	parentNode = parentNodeRef;
	physicsEngine = physicsEngineRef;

	std::cout << "AI Manager Initialized." <<std::endl;
}
void aiManager::trainNewShip(Ogre::Vector3 position)
{

}