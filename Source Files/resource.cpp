#include "resource.h"

Resource::Resource(RESOURCE_TYPE type, float value): myType(type), myValue(value)
{
}
Resource::~Resource()
{
}
Resource::RESOURCE_TYPE Resource::getType()
{
	return myType;
}

float Resource::getValue()
{
	return myValue;
}