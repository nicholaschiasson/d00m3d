#ifndef CAMERA_H
#define CAMERA_H

#include <OgreCamera.h>
#include <OgreSceneNode.h>

#define CAMERA_INITIAL_DISTANCE 2.0
class Camera
{
public:
	Camera();
	~Camera();

	/*	initCamera();
	*	in:			Ogre's camera object to be built around
	*	in:			The scene Node the camera should initially be attached to
	*	Purpose:	To set up the camera for use
	*/
	void initCamera(Ogre::Camera* cam, Ogre::SceneNode* followNode);

	/*	attachTo
	*	in:			SceneNode you wish to attach
	*	Purpose:	To attach the camera to a Node, this will be attached starting  at a certain distance away (can be specified with the setDistance function)
	*/
	void attachTo(Ogre::SceneNode* followNode);

	/*	setDistance
	*	in:			float, the distance you wish to be behind the attached node, can be negative
	*	Purpose:	to set the distnace away from a node you wish the camera to be (0 for first person, negative to turn camera around)
	*/
	void setDistance(const float distanceFromNode);

	void rotate(const Ogre::Quaternion& rot);

	void yaw(const Ogre::Radian& angle);
	void pitch(const Ogre::Radian& angle);
	void roll(const Ogre::Radian& angle);

	Ogre::Vector3 getDirection() const;
	Ogre::Vector3 getUp() const;
	Ogre::Vector3 getSide() const;
	Ogre::Vector3 getPosition() const;

	void getAxis();

private:
	Ogre::Camera* camera;
	Ogre::SceneNode* cameraNode;
	float distance;

};
#endif