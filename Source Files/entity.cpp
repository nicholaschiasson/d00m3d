#include "entity.h"

#include "defines.h"

unsigned int Entity::entityCount = 0;

Entity::Entity(): sceneNode(NULL)
{
}

Entity::~Entity()
{
}

void Entity::kill()
{
	alive = false;
	health = 0;
}

void Entity::spaghettify()
{
	kill();
	spaghettified = true;
}

void Entity::cleanup()
{
	if(sceneNode){
		sceneNode->getParentSceneNode()->removeAndDestroyChild(sceneNode->getName());
		sceneNode = NULL;
	}
}

void Entity::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, unsigned int parentID)
{
	objectID = entityCount;
	parentObjectID = parentID;
	
	//only if we have not already initialized
	if(sceneNode == NULL){
		sceneNode = parentNode->createChildSceneNode("Entity" + Ogre::StringConverter::toString(entityCount++));
	}
	alive = true;
	health = 100.0f;
	durability = 1.0f;
	spaghettified = false;
}

void Entity::Update(const Ogre::FrameEvent &fe)
{
	if (alive)
	{
		if (health <= 0.0f)
		{
			kill();
		}
	}
}

void Entity::Damage(float damage)
{
	if (alive)
	{
		if (durability == 0.0f)
		{
			health = 0.0f;
		}
		else
		{
			health = max(0.0f, health - (damage / durability));
		}
	}
}
Resource Entity::collect(Entity* entity)
{
	return Resource(Resource::NONE, 0.0f);
}

void Entity::explode()
{
	//lalala
}
unsigned int Entity::GetObjectID()
{
	return objectID;
}

unsigned int Entity::GetParentID()
{
	return parentObjectID;
}

void Entity::addChild(Ogre::Node *child)
{
	if (sceneNode)
	{
		sceneNode->addChild(child);
	}
}

void Entity::pitch(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->pitch(angle, relativeTo);
	}
}

void Entity::rotate(const Ogre::Quaternion &q, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->rotate(q, relativeTo);
	}
}

void Entity::rotate(const Ogre::Vector3 &axis, const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->rotate(axis, angle, relativeTo);
	}
}

void Entity::roll(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->roll(angle, relativeTo);
	}
}

void Entity::scale(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	if (sceneNode)
	{
		sceneNode->scale(x, y, z);
	}
}

void Entity::scale(const Ogre::Vector3 &scale)
{
	if (sceneNode)
	{
		sceneNode->scale(scale);
	}
}

void Entity::translate(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->translate(x, y, z, relativeTo);
	}
}

void Entity::translate(const Ogre::Vector3 &d, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->translate(d, relativeTo);
	}
}

void Entity::translate(const Ogre::Matrix3 &axes, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->translate(axes, x, y, z, relativeTo);
	}
}

void Entity::translate(const Ogre::Matrix3 &axes, const Ogre::Vector3 &move, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->translate(axes, move, relativeTo);
	}
}

void Entity::yaw(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo)
{
	if (sceneNode)
	{
		sceneNode->yaw(angle, relativeTo);
	}
}

const Ogre::String & Entity::getName() const
{
	return sceneNode->getName();
}

Ogre::Vector3 Entity::getPosition() const
{
	return sceneNode->getPosition();
}

Ogre::Vector3 Entity::getDerivedPosition() const
{
	return sceneNode->_getDerivedPosition();
}

Ogre::Quaternion Entity::getOrientation() const
{
	return sceneNode->getOrientation();
}

Ogre::Quaternion Entity::getDerivedOrientation() const
{
	return sceneNode->_getDerivedOrientation();
}

bool Entity::isAlive() const
{
	return alive;
}

bool Entity::isSpaghettified() const
{
	return spaghettified;
}