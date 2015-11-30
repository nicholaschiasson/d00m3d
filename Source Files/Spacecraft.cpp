#include "spacecraft.h"

#include "OgreEntity.h"

Spacecraft::Spacecraft() :
	materialPrefix("Player"), light(Ogre::Vector3(0.0f, 0.0f, 0.0f)), leftPanelPivot(0), rightPanelPivot(0),
	thrusterForce(500.0f), weapon(new LaserCannon())
{
	artillerySystems.push_back(SystemComponent(SystemComponent::SYSTEM_ARTILLERY, 100.0f, 100.0f));
	defenseSystems.push_back(SystemComponent(SystemComponent::SYSTEM_DEFENSE, 100.0f, 0.0f));
	fuelSystems.push_back(SystemComponent(SystemComponent::SYSTEM_FUEL, 100.0f, 100.0f));
	navigationalSystems.push_back(SystemComponent(SystemComponent::SYSTEM_NAVIGATIONAL, 100.0f, 0.0f)); // nav should probably always have value of 0
}

Spacecraft::~Spacecraft()
{
	
}

void Spacecraft::cleanup(PhysicsEngine &physicsEngine)
{
	weapon->detachFrom(physicsEngine);
	PhysicsEntity::cleanup(physicsEngine);
}

void Spacecraft::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, PhysicsEngine &physicsEngine, Ogre::Vector3 lightPos, ParticleEngine *particleEngine, unsigned int parentID)
{
	PhysicsEntity::Initialize(sceneManager, parentNode, physicsEngine, parentID);
	mass = 5000.0f;
	//dynamic = false;

	light = lightPos;

	unsigned int pid = (parentID == -1 ? objectID : parentID);
	
	float spacecraftScaleX = 1.6f, spacecraftScaleY = 0.6f, spacecraftScaleZ = 1.0f;
	float invSpacecraftScaleX = 1.0f / spacecraftScaleX, invSpacecraftScaleY = 1.0f / spacecraftScaleY, invSpacecraftScaleZ = 1.0f / spacecraftScaleZ;
	Ogre::Entity *spacecraftBodyEntity = sceneManager->createEntity("Cylinder");
	spacecraftBodyEntity->setMaterialName(materialPrefix + "SpacecraftLongMaterial");
	Ogre::SceneNode *spacecraftBodyNode = sceneNode->createChildSceneNode("SpacecraftBody" + Ogre::StringConverter::toString(entityCount));
	//Ogre::SceneNode *spacecraftBodyNode = parentNode->createChildSceneNode("SpacecraftBody" + Ogre::StringConverter::toString(entityCount));
	spacecraftBodyNode->attachObject(spacecraftBodyEntity);
	spacecraftBodyNode->scale(0.75f, 0.75f, 0.75f);
	spacecraftBodyNode->scale(spacecraftScaleX, spacecraftScaleY, spacecraftScaleZ);
	spacecraftBodyNode->pitch(-Ogre::Radian(Ogre::Math::HALF_PI));

	Ogre::Entity *spacecraftLeftThrusterEntity = sceneManager->createEntity("Torus");
	spacecraftLeftThrusterEntity->setMaterialName("SpacecraftThrusterMaterial");
	Ogre::SceneNode *spacecraftLeftThrusterNode = spacecraftBodyNode->createChildSceneNode("SpacecraftLeftThruster" + Ogre::StringConverter::toString(entityCount));
	spacecraftLeftThrusterNode->attachObject(spacecraftLeftThrusterEntity);
	spacecraftLeftThrusterNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftLeftThrusterNode->scale(0.4f, 0.4f, 2.0f);
	spacecraftLeftThrusterNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftLeftThrusterNode->translate(-0.1f, -0.3f, 0.0f);
	
	Ogre::Entity *spacecraftRightThrusterEntity = sceneManager->createEntity("Torus");
	spacecraftRightThrusterEntity->setMaterialName("SpacecraftThrusterMaterial");
	Ogre::SceneNode *spacecraftRightThrusterNode = spacecraftBodyNode->createChildSceneNode("SpacecraftRightThruster" + Ogre::StringConverter::toString(entityCount));
	spacecraftRightThrusterNode->attachObject(spacecraftRightThrusterEntity);
	spacecraftRightThrusterNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftRightThrusterNode->scale(0.4f, 0.4f, 2.0f);
	spacecraftRightThrusterNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftRightThrusterNode->translate(0.1f, -0.3f, 0.0f);
	
	Ogre::Entity *spacecraftLeftWingEntity = sceneManager->createEntity("Pyramid");
	spacecraftLeftWingEntity->setMaterialName(materialPrefix + "SpacecraftMediumMaterial");
	Ogre::SceneNode *spacecraftLeftWingNode = spacecraftBodyNode->createChildSceneNode("SpacecraftLeftWing" + Ogre::StringConverter::toString(entityCount));
	spacecraftLeftWingNode->attachObject(spacecraftLeftWingEntity);
	spacecraftLeftWingNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftLeftWingNode->scale(0.8f, 0.5f, 0.3f);
	spacecraftLeftWingNode->roll(Ogre::Radian(Ogre::Math::HALF_PI));
	spacecraftLeftWingNode->translate(-0.375f, 0.0f, 0.0f);
	
	Ogre::Entity *spacecraftRightWingEntity = sceneManager->createEntity("Pyramid");
	spacecraftRightWingEntity->setMaterialName(materialPrefix + "SpacecraftMediumMaterial");
	Ogre::SceneNode *spacecraftRightWingNode = spacecraftBodyNode->createChildSceneNode("SpacecraftRightWing" + Ogre::StringConverter::toString(entityCount));
	spacecraftRightWingNode->attachObject(spacecraftRightWingEntity);
	spacecraftRightWingNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	spacecraftRightWingNode->scale(0.8f, 0.5f, 0.3f);
	spacecraftRightWingNode->roll(Ogre::Radian(-Ogre::Math::HALF_PI));
	spacecraftRightWingNode->translate(0.375f, 0.0f, 0.0f);

	Ogre::Entity *spacecraftNoseEntity = sceneManager->createEntity("Sphere");
	spacecraftNoseEntity->setMaterialName(materialPrefix + "SpacecraftLongMaterial");
	Ogre::SceneNode *spacecraftNoseNode = spacecraftBodyNode->createChildSceneNode("SpacecraftNose" + Ogre::StringConverter::toString(entityCount));
	spacecraftNoseNode->attachObject(spacecraftNoseEntity);
	spacecraftNoseNode->scale(0.502f, 1.5f, 0.502f);
	spacecraftNoseNode->translate(0.0f, 0.45f, 0.0f);
	
	Ogre::Entity *spacecraftPodEntity = sceneManager->createEntity("SphereScreen");
	spacecraftPodEntity->setMaterialName("SpacecraftPodMaterial");
	Ogre::SceneNode *spacecraftPodNode = spacecraftNoseNode->createChildSceneNode("SpacecraftPod" + Ogre::StringConverter::toString(entityCount));
	spacecraftPodNode->attachObject(spacecraftPodEntity);
	spacecraftPodNode->scale(0.6f, 0.5f, 0.5f);
	spacecraftPodNode->pitch(Ogre::Radian(-Ogre::Math::PI / 5.5f));
	spacecraftPodNode->translate(0.0f, 0.28f, 0.175f);

	Ogre::Entity *leftPanelArmEntity = sceneManager->createEntity("Cylinder");
	leftPanelArmEntity->setMaterialName(materialPrefix + "SpacecraftShortMaterial");
	Ogre::SceneNode *leftPanelArmNode = spacecraftBodyNode->createChildSceneNode("LeftPanelArm" + Ogre::StringConverter::toString(entityCount));
	leftPanelArmNode->attachObject(leftPanelArmEntity);
	leftPanelArmNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	leftPanelArmNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	leftPanelArmNode->scale(0.1f, 0.25f, 0.1f);
	leftPanelArmNode->roll(Ogre::Radian(Ogre::Math::PI / 6.0f));
	leftPanelArmNode->translate(-0.2f, 0.0f, 0.3f);

	Ogre::Entity *leftPanelPivotEntity = sceneManager->createEntity("Sphere");
	leftPanelPivotEntity->setMaterialName(materialPrefix + "SpacecraftMediumMaterial");
	leftPanelPivot = leftPanelArmNode->createChildSceneNode("LeftPanelPivot" + Ogre::StringConverter::toString(entityCount));
	leftPanelPivot->attachObject(leftPanelPivotEntity);
	leftPanelPivot->scale(1.0f / 0.1f, 1.0f / 0.25f, 1.0f / 0.1f);
	leftPanelPivot->scale(0.1f, 0.1f, 0.1f);
	leftPanelPivot->roll(-Ogre::Radian(Ogre::Math::PI / 6.0f));
	leftPanelPivot->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	leftPanelPivot->translate(0.0f, 0.65f, 0.0f);

	Ogre::Entity *leftPanelEntity = sceneManager->createEntity("Cube");
	leftPanelEntity->setMaterialName("SpacecraftPanelMaterial");
	Ogre::SceneNode *leftPanelNode = leftPanelPivot->createChildSceneNode("LeftPanel" + Ogre::StringConverter::toString(entityCount));
	leftPanelNode->attachObject(leftPanelEntity);
	leftPanelNode->scale(1.0f / 0.1f, 1.0f / 0.1f, 1.0f / 0.1f);
	leftPanelNode->scale(0.5f, 0.01f, 0.75f);
	leftPanelNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));

	Ogre::Entity *rightPanelArmEntity = sceneManager->createEntity("Cylinder");
	rightPanelArmEntity->setMaterialName(materialPrefix + "SpacecraftShortMaterial");
	Ogre::SceneNode *rightPanelArmNode = spacecraftBodyNode->createChildSceneNode("RightPanelArm" + Ogre::StringConverter::toString(entityCount));
	rightPanelArmNode->attachObject(rightPanelArmEntity);
	rightPanelArmNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	rightPanelArmNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	rightPanelArmNode->scale(0.1f, 0.25f, 0.1f);
	rightPanelArmNode->roll(-Ogre::Radian(Ogre::Math::PI / 6.0f));
	rightPanelArmNode->translate(0.2f, 0.0f, 0.3f);

	Ogre::Entity *rightPanelPivotEntity = sceneManager->createEntity("Sphere");
	rightPanelPivotEntity->setMaterialName(materialPrefix + "SpacecraftMediumMaterial");
	rightPanelPivot = rightPanelArmNode->createChildSceneNode("RightPanelPivot" + Ogre::StringConverter::toString(entityCount));
	rightPanelPivot->attachObject(rightPanelPivotEntity);
	rightPanelPivot->scale(1.0f / 0.1f, 1.0f / 0.25f, 1.0f / 0.1f);
	rightPanelPivot->scale(0.1f, 0.1f, 0.1f);
	rightPanelPivot->roll(Ogre::Radian(Ogre::Math::PI / 6.0f));
	rightPanelPivot->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	rightPanelPivot->translate(0.0f, 0.65f, 0.0f);

	Ogre::Entity *rightPanelEntity = sceneManager->createEntity("Cube");
	rightPanelEntity->setMaterialName("SpacecraftPanelMaterial");
	Ogre::SceneNode *rightPanelNode = rightPanelPivot->createChildSceneNode("RightPanel" + Ogre::StringConverter::toString(entityCount));
	rightPanelNode->attachObject(rightPanelEntity);
	rightPanelNode->scale(1.0f / 0.1f, 1.0f / 0.1f, 1.0f / 0.1f);
	rightPanelNode->scale(0.5f, 0.01f, 0.75f);
	rightPanelNode->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));

	Ogre::Entity *weaponArmEntity = sceneManager->createEntity("Cylinder");
	weaponArmEntity->setMaterialName(materialPrefix + "SpacecraftShortMaterial");
	Ogre::SceneNode *weaponArmNode = spacecraftBodyNode->createChildSceneNode("WeaponArm" + Ogre::StringConverter::toString(entityCount));
	weaponArmNode->attachObject(weaponArmEntity);
	weaponArmNode->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	weaponArmNode->scale(invSpacecraftScaleX, invSpacecraftScaleY, invSpacecraftScaleZ);
	weaponArmNode->scale(0.1f, 0.2f, 0.1f);
	weaponArmNode->translate(0.0f, 0.0f, -((0.2f * 0.5f) + ((0.75f * spacecraftScaleY) * 0.5f)));

	weapon->Initialize(sceneManager, weaponArmNode, parentNode, physicsEngine, particleEngine, pid);
	weapon->scale(1.0f / 0.1f, 1.0f / 0.2f, 1.0f / 0.1f);
	weapon->translate(0.0f, -0.9f, 0.0f);
	
}

float Spacecraft::getDefense()
{
	std::cout << "WARNING: getDefense() deprecated" <<std::endl; 
	if (defenseSystems.size() > 0)
	{
		return defenseSystems.front().getValue();
	}
	return 0.0f;
}

float Spacecraft::getEnergy()
{
	std::cout << "WARNING: getEnergy() deprecated" <<std::endl;
	if (artillerySystems.size() > 0)
	{
		return artillerySystems.front().getValue();
	}
	return 0.0f;
}
float Spacecraft::getFuel()
{
	std::cout << "WARNING: getFuel() deprecated" <<std::endl;
	if (fuelSystems.size() > 0)
	{
		return fuelSystems.front().getValue();
	}
	return 0.0f;
}

void Spacecraft::Update(const Ogre::FrameEvent &fe)
{
	PhysicsEntity::Update(fe);

	if(alive)
	{
		if (velocity.squaredLength() > 10000.0f)
		{
			velocity = velocity.normalisedCopy() * 100.0f;
		}
        
		Ogre::Quaternion orientation = leftPanelPivot->getOrientation();
		leftPanelPivot->resetOrientation();
		leftPanelPivot->roll(-Ogre::Radian(Ogre::Math::PI / 6.0f));
		leftPanelPivot->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
        Ogre::Vector3 dir = light - leftPanelPivot->_getDerivedPosition();
        Ogre::Vector3 ori = leftPanelPivot->_getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
        Ogre::Radian theta = ori.angleBetween(dir);
		leftPanelPivot->setOrientation(orientation);
		if (theta <= Ogre::Radian(Ogre::Math::PI / 4.0f))
		{
			leftPanelPivot->lookAt(light, Ogre::Node::TS_WORLD);
		}
        
		orientation = rightPanelPivot->getOrientation();
		rightPanelPivot->resetOrientation();
		rightPanelPivot->roll(Ogre::Radian(Ogre::Math::PI / 6.0f));
		rightPanelPivot->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
        dir = light - rightPanelPivot->_getDerivedPosition();
        ori = rightPanelPivot->_getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
        theta = ori.angleBetween(dir);
		rightPanelPivot->setOrientation(orientation);
		if (theta <= Ogre::Radian(Ogre::Math::PI / 4.0f))
		{
			rightPanelPivot->lookAt(light, Ogre::Node::TS_WORLD);
		}
		
		if (artillerySystems.size() > 0 && artillerySystems.front().getHealth() <= 0.0f)
		{
			artillerySystems.pop_front();
		}
		
		if (defenseSystems.size() > 0 && defenseSystems.front().getHealth() <= 0.0f)
		{
			defenseSystems.pop_front();
		}
		
		if (fuelSystems.size() > 0 && fuelSystems.front().getHealth() <= 0.0f)
		{
			fuelSystems.pop_front();
		}
		
		if (navigationalSystems.size() > 0 && navigationalSystems.front().getHealth() <= 0.0f)
		{
			navigationalSystems.pop_front();
		}

		weapon->Update(fe, velocity);
	}
}

void Spacecraft::Damage(float damage)
{
	if(alive){
		int randomval = rand() % 2;
		if(randomval == 0){ //Hit the defenses
			if(defenseSystems.size() == 0){
				PhysicsEntity::Damage(damage);
			}
			else{
				defenseSystems.front().damage(damage);
			}
		}
		else{ //Damage System
			randomval = rand() % 3;
			switch(randomval){
			case 0:
				if(artillerySystems.size() == 0){
					PhysicsEntity::Damage(damage);
				}
				else{
					artillerySystems.front().damage(damage);
				}
				break;
			case 1:
				if(navigationalSystems.size() == 0){
					PhysicsEntity::Damage(damage);
				}
				else{
					navigationalSystems.front().damage(damage);
				}
				break;
			case 2:
				if(fuelSystems.size() == 0){
					PhysicsEntity::Damage(damage);
				}
				else{
					fuelSystems.front().damage(damage);
				}
				break;
			}
		}
	}
}

float Spacecraft::getSpeed()
{
	return velocity.squaredLength();
}

void Spacecraft::Collide(const Ogre::FrameEvent &fe, PhysicsEntity *physicsEntity)
{
	Resource resource = physicsEntity->collect(this);

	//todo implement tracking
	switch(resource.getType()){
	case Resource::FUEL:
		for(std::list<SystemComponent>::iterator it = fuelSystems.begin(); it != fuelSystems.end(); ++it){
			if (it->getValue() != 100)
			{
				it->addValue(resource.getValue());
				it->setValue(std::min(it->getValue(), 100.0f));
			}
		}
		break;
	case Resource::ENERGY:
		for(std::list<SystemComponent>::iterator it = artillerySystems.begin(); it != artillerySystems.end(); ++it){
			if (it->getValue() != 100)
			{
				it->addValue(resource.getValue());
				it->setValue(std::min(it->getValue(), 100.0f));
			}
		}
		break;
	case Resource::PARTS:
		for(std::list<SystemComponent>::iterator it = defenseSystems.begin(); it != defenseSystems.end(); ++it){
			if (it->getValue() != 100)
			{
				it->addHealth(resource.getValue());
				it->setHealth(std::min(it->getHealth(), 100.0f));
			}
		}
		break;
	case Resource::BACKUP:
		switch ((SystemComponent::SYSTEM_TYPE)((int)resource.getValue()))
		{
		case SystemComponent::SYSTEM_ARTILLERY:
			artillerySystems.push_back(SystemComponent(SystemComponent::SYSTEM_ARTILLERY, 100.0f, 100.0f));
			break;
		case SystemComponent::SYSTEM_DEFENSE:
			defenseSystems.push_back(SystemComponent(SystemComponent::SYSTEM_DEFENSE, 100.0f, 0.0f));
			break;
		case SystemComponent::SYSTEM_FUEL:
			fuelSystems.push_back(SystemComponent(SystemComponent::SYSTEM_FUEL, 100.0f, 100.0f));
			break;
		case SystemComponent::SYSTEM_NAVIGATIONAL:
			navigationalSystems.push_back(SystemComponent(SystemComponent::SYSTEM_NAVIGATIONAL, 100.0f, 0.0f)); // nav should probably always have value of 0
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Spacecraft::spaghettify()
{

}

PhysicsEntity *Spacecraft::fireWeapon()
{
	if(weapon->getState() == Weapon::WEAPON_READY){
		return weapon->fire();
	}
	return 0;
}

void Spacecraft::ThrustersForward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

	ApplyForce(playerDirection.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersLeft()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
	ApplyForce(-playerRight.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersBackward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerDirection = playerOrientation * Ogre::Vector3::NEGATIVE_UNIT_Z;

	ApplyForce(-playerDirection.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersRight()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerRight = playerOrientation * Ogre::Vector3::UNIT_X;
		
	ApplyForce(playerRight.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersUpward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
	ApplyForce(playerUp.normalisedCopy() * thrusterForce);
}

void Spacecraft::ThrustersDownward()
{
	Ogre::Quaternion playerOrientation = sceneNode->getOrientation();
	Ogre::Vector3 playerUp = playerOrientation * Ogre::Vector3::UNIT_Y;
		
	ApplyForce(-playerUp.normalisedCopy() * thrusterForce);
}

SystemComponent* Spacecraft::getActiveSystem(SystemComponent::SYSTEM_TYPE system)
{
	SystemComponent* activeComponent = NULL;
	switch(system){
	case SystemComponent::SYSTEM_ARTILLERY:
		if(artillerySystems.size() > 0){
			activeComponent =  &(artillerySystems.front());
		}
		break;
	case SystemComponent::SYSTEM_DEFENSE:
		if(defenseSystems.size() > 0){
			activeComponent = &(defenseSystems.front());
		}
		break;
	case SystemComponent::SYSTEM_FUEL:
		if(fuelSystems.size() > 0){
			activeComponent =  &(fuelSystems.front());
		}
		break;
	case SystemComponent::SYSTEM_NAVIGATIONAL:
		if(navigationalSystems.size() > 0){
			activeComponent = &(navigationalSystems.front());
		}
		break;
	}

	return activeComponent;
}
int Spacecraft::getNumSystemBackups(SystemComponent::SYSTEM_TYPE system)
{
	switch(system){
	case SystemComponent::SYSTEM_ARTILLERY:
		return artillerySystems.size() -1; //removing the one we currently using
	case SystemComponent::SYSTEM_DEFENSE:
		return defenseSystems.size() - 1;
	case SystemComponent::SYSTEM_FUEL:
		return fuelSystems.size() -1;
	case SystemComponent::SYSTEM_NAVIGATIONAL:
		return navigationalSystems.size() -1;
	default:
		return 0;
	}
}