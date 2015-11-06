#include "camera.h"

Camera::Camera(): camera(NULL), distance(CAMERA_INITIAL_DISTANCE)
{

}
Camera::~Camera()
{
	//TODO MEMORY MANAGEMENT
}

void Camera::attachTo(const Ogre::SceneNode* followNode)
{
	//TODO move the hooking up a camera from the ogre_application to here
}
void Camera::setDistance(const float distanceFromNode)
{
	distance = distanceFromNode;
}

void Camera::initCamera(Ogre::Camera* ogreCamera)
{
	camera = ogreCamera;
}