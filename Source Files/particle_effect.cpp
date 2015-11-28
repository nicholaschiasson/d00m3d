#include "particle_effect.h"

ParticleEffect::ParticleEffect(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine):
	timer(0), duration(3 + ((float) rand() / (float) (RAND_MAX /4)))
{
	Initialize(sceneManager, parentNode, object_name, material_name, physicsEngine);
}

void ParticleEffect::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);

	 Ogre::Entity* entity = sceneManager->createEntity(object_name);

	/* Apply a material to the entity */
	 materialName = material_name;
	entity->setMaterialName(materialName);

	sceneNode->attachObject(entity);
	sceneNode->translate(0,0,0);
	
}
void ParticleEffect::Update(const Ogre::FrameEvent& fe)
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

void ParticleEffect::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
}
