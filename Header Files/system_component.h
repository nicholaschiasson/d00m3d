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
	float getValue();

	void setValue(float v);

private:
	float health;
	SYSTEM_TYPE type;
	float value;

};

#endif // SYSTEM_COMPONENT_H