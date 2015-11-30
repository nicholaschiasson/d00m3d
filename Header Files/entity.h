#ifndef ENTITY_H
#define ENTITY_H

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "resource.h"

//#include "item.h"

class Entity
{
public:
	Entity();
	virtual ~Entity() = 0;

	virtual void Initialize(Ogre::SceneManager *sceneManager, Ogre::SceneNode* parentNode, unsigned int parentID = -1);
	virtual void Update(const Ogre::FrameEvent &fe);
	
	//virtual void Collect(Item *item);
	virtual void Damage(float damage);
	virtual void explode();

	virtual unsigned int GetObjectID();
	virtual unsigned int GetParentID();

	// SceneNode functionality
	virtual void addChild(Ogre::Node *child);
	virtual void pitch(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	virtual void rotate(const Ogre::Quaternion &q, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	virtual void rotate(const Ogre::Vector3 &axis, const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	virtual void roll(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	virtual void scale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
	virtual void scale(const Ogre::Vector3 &scale);
	virtual void translate(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT);
	virtual void translate(const Ogre::Vector3 &d, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT);
	virtual void translate(const Ogre::Matrix3 &axes, Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT);
	virtual void translate(const Ogre::Matrix3 &axes, const Ogre::Vector3 &move, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT);
	virtual void yaw(const Ogre::Radian &angle, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	
	virtual void setDerivedOrientation(const Ogre::Quaternion &q);
	virtual void setOrientation(Ogre::Real w, Ogre::Real x, Ogre::Real y, Ogre::Real z);
	virtual void setOrientation(const Ogre::Quaternion &q);
	virtual void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
	virtual void setScale(const Ogre::Vector3 &scale);

	virtual const Ogre::String & getName() const;
	virtual Ogre::Vector3 getPosition() const;
	virtual Ogre::Vector3 Entity::getDerivedPosition() const;
	virtual Ogre::Quaternion getOrientation() const;
	virtual Ogre::Quaternion getDerivedOrientation() const;
	virtual bool isAlive() const;
	virtual bool isSpaghettified() const;
	virtual Resource collect(Entity* entity);
	
	/*
	*	Sets player to dead (alive false)
	*
	*/
	virtual void kill();
	
	/*
	*	Marks player as being killed by black hole (spaghettified true)
	*
	*/
	virtual void spaghettify();

	/*	cleanup()
	*	Purpose:	To clean up all the resources attached to this entity, should only be called when deleting the object if you have not removed the sceneNode
	*
	*/
	virtual void cleanup();

protected:
	static unsigned int entityCount;

	Ogre::SceneNode *sceneNode;
	bool alive;
	float health;
	float durability;
	bool spaghettified; // absolute death

	unsigned int objectID;
	unsigned int parentObjectID;

private:


};

#endif // ENTITY_H
