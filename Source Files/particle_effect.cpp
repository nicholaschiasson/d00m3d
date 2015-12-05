#include "particle_effect.h"

ParticleEffect::ParticleEffect(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine, float dur, unsigned int parentID):
	timer(0), duration(dur)
{
	Initialize(sceneManager, parentNode, object_name, material_name, physicsEngine, parentID);
}

void ParticleEffect::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, Ogre::String object_name, Ogre::String material_name, PhysicsEngine &physicsEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	bodyType = ENTITY_BODY_METAPHYSICAL;

	 Ogre::Entity* entity = sceneManager->createEntity(object_name);

	/* Apply a material to the entity */
	materialName = material_name + std::to_string(objectID);
	Ogre::MaterialPtr origMat = Ogre::MaterialManager::getSingleton().getByName(material_name);
	Ogre::Material* mat = origMat.get();
	mat->clone(materialName);
	entity->setMaterialName(materialName);

	sceneNode->attachObject(entity);
	sceneNode->translate(0,0,0);
	
}
void ParticleEffect::Update(const Ogre::FrameEvent& fe)
{
	PhysicsEntity::Update(fe);
	if(alive){
		timer += fe.timeSinceLastFrame;
		//std::cout << "Passing in Timer: " <<timer <<std::endl;
		Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(materialName));
		mat->getBestTechnique()->getPass(0)->getVertexProgramParameters()->setNamedConstant("timer", timer);

		if(duration > 0.0f && timer > duration){
			alive = false;
		}
	}
}

void ParticleEffect::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
}
