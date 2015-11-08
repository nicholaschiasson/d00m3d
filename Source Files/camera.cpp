#include "camera.h"

Camera::Camera(): camera(NULL), cameraNode(NULL), distance(CAMERA_INITIAL_DISTANCE)
{

}
Camera::~Camera()
{
	//TODO MEMORY MANAGEMENT
}

void Camera::initCamera(Ogre::Camera* ogreCamera, Ogre::SceneNode* followNode)
{
	if(ogreCamera == NULL || followNode == NULL){
		throw std::runtime_error("Passed Null as Ogre::Camera /Ogre::SceneNode");
	}
	camera = ogreCamera;
	cameraNode = followNode->createChildSceneNode("cameraNode");
	cameraNode->attachObject(camera);
}


void Camera::attachTo(Ogre::SceneNode* followNode)
{
	//TODO move the hooking up a camera from the ogre_application to here
	if(camera == NULL){
		throw std::runtime_error("Camera not initialized");
	}
	cameraNode->getParentSceneNode()->removeChild(cameraNode->getName());
	followNode->addChild(cameraNode);
	cameraNode->setPosition(0,0,0);

}
void Camera::setDistance(const float distanceFromNode)
{
	distance = distanceFromNode;
}

void Camera::rotate(const Ogre::Quaternion& rot)
{
	camera->rotate(rot);
}

void Camera::yaw(const Ogre::Radian& angle)
{
	camera->yaw(angle);
}
void Camera::pitch(const Ogre::Radian& angle)
{
	camera->pitch(angle);
}
void Camera::roll(const Ogre::Radian& angle)
{
	camera->roll(angle);
}

Ogre::Vector3 Camera::getDirection() const
{
	return camera->getDirection();
}
Ogre::Vector3 Camera::getUp() const
{
	return camera->getUp();
}
Ogre::Vector3 Camera::getSide() const
{
	return camera->getRight();
}
Ogre::Vector3 Camera::getPosition() const
{
	return camera->getPosition();
}