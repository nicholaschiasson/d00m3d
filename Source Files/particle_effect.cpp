#include "particle_effect.h"

ParticleEffect::ParticleEffect(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine,  Ogre::Vector3 position)
{
	Initialize(sceneManager, parentNode, object_name, material_name, physicsEngine, position);
}

void ParticleEffect::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine, Ogre::Vector3 position, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	 Ogre::Entity* entity = sceneManager->createEntity(object_name);

	/* Apply a material to the entity */
	 materialName = material_name;
	entity->setMaterialName(materialName);

	sceneNode->attachObject(entity);
	sceneNode->translate(position);
	
}
void ParticleEffect::update(const Ogre::FrameEvent& fe)
{
	if(alive){
		timer += fe.timeSinceLastFrame;
		Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(materialName));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer);

		if(timer > duration){
			alive = false;
		}
	}
}