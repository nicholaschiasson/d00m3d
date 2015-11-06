#include "camera.h"

Camera::Camera(Ogre::Camera* cam): camera(cam), distance(CAMERA_INITIAL_DISTANCE)
{

}
Camera::~Camera()
{
	//TODO MEMORY MANAGEMENT
}

void Camera::attachTo(Ogre::SceneNode* followNode)
{
	//TODO move the hooking up a camera from the ogre_application to here
}
void Camera::setDistance(float distanceFromNode)
{
	distance = distanceFromNode;
}