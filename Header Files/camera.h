#ifndef CAMERA_H
#define CAMERA_H

#include "ogre_application.h"

#define CAMERA_INITIAL_DISTANCE 2.0
class Camera
{
public:
	Camera(Ogre::Camera* cam);
	~Camera();

	/*	attachTo
	*	in:			SceneNode you wish to attach
	*	Purpose:	To attach the camera to a Node, this will be attached starting  at a certain distance away (can be specified with the setDistance function)
	*/
	void attachTo(Ogre::SceneNode* followNode);

	/*	setDistance
	*	in:			float, the distance you wish to be behind the attached node, can be negative
	*	Purpose:	to set the distnace away from a node you wish the camera to be (0 for first person, negative to turn camera around)
	*/
	void setDistance(float distanceFromNode);

private:
	Ogre::Camera* camera;
	float distance;

};
#endif