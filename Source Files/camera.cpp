#include "camera.h"

Camera::Camera(): camera(NULL), cameraNode(NULL)
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
	camera->lookAt(cameraNode->_getDerivedPosition() + (cameraNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z) * 100.0f);
	setDistance(Ogre::Vector3(0, 0.5f, 2));
}


void Camera::attachTo(Entity* followEntity)
{
	//TODO move the hooking up a camera from the ogre_application to here
	if(camera == NULL){
		throw std::runtime_error("Camera not initialized");
	}
	cameraNode->getParentSceneNode()->removeChild(cameraNode->getName());
	followEntity->addChild(cameraNode);
	cameraNode->setPosition(0,0,0);

}
void Camera::setDistance(const Ogre::Vector3 positionFromNode)
{
	camera->setPosition(cameraNode->_getDerivedPosition() + positionFromNode);
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

void Camera::orbit(const Ogre::Quaternion& rot)
{
	cameraNode->rotate(rot);
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