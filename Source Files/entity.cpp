#include "entity.h"

#include "defines.h"

unsigned int Entity::entityCount = 0;

Entity::Entity()
{
	sceneNode = 0;
	alive = true;
	health = 100.0f;
	durability = 1.0f;
}

Entity::~Entity()
{
}

void Entity::Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode)
{
	sceneNode = parentNode->createChildSceneNode("Entity" + Ogre::StringConverter::toString(entityCount++));
}

void Entity::Update(const Ogre::FrameEvent &fe)
{
	if (alive)
	{
		if (health <= 0.0f)
		{
			alive = false;
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