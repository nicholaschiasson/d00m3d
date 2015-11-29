#include "system_component.h"

SystemComponent::SystemComponent(SystemComponent::SYSTEM_TYPE t, float h, float v) :
	type(t), health(h), value(v)
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

void SystemComponent::addHealth(float h)
{
	health += h;
};

void SystemComponent::addValue(float v)
{
	value += v;
}

void SystemComponent::setHealth(float h)
{
	health = h;
};

void SystemComponent::setValue(float v)
{
	value = v;
}

void SystemComponent::damage(float d)
{
	health = std::max(health -d, 0.0f);
}