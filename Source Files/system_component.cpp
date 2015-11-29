#include "system_component.h"

SystemComponent::SystemComponent()
{
}

SystemComponent::~SystemComponent()
{
}

float SystemComponent::getHealth()
{
	return health;
}

Ogre::String SystemComponent::getName()
{
	switch (type)
	{
	case SYSTEM_ARTILLERY:
		return "Artillery";
	case SYSTEM_DEFENSE:
		return "Defense";
	case SYSTEM_FUEL:
		return "Fuel";
	case SYSTEM_NAVIGATIONAL:
		return "Navigational";
	default:
		return "Unknown";
	}
}

SystemComponent::SYSTEM_TYPE SystemComponent::getType()
{
	return type;
}

float SystemComponent::getValue()
{
	return value;
}

void SystemComponent::setValue(float v)
{
	value = v;
}