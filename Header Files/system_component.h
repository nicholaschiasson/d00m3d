#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include <OgreString.h>

class SystemComponent
{
public:
	enum SYSTEM_TYPE
	{
		SYSTEM_ARTILLERY,
		SYSTEM_DEFENSE,
		SYSTEM_FUEL,
		SYSTEM_NAVIGATIONAL,
	};

	SystemComponent();
	~SystemComponent();

	float getHealth();
	Ogre::String getName();
	SYSTEM_TYPE getType();

private:
	float health;
	SYSTEM_TYPE type;

};

#endif // SYSTEM_COMPONENT_H