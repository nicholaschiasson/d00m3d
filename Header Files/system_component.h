#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include <OgreString.h>

class SystemComponent
{
public:
	enum SYSTEM_TYPE
	{
		SYSTEM_UNKNOWN,
		SYSTEM_ARTILLERY,
		SYSTEM_DEFENSE,
		SYSTEM_FUEL,
		SYSTEM_NAVIGATIONAL,
	};

	SystemComponent(SYSTEM_TYPE t = SYSTEM_UNKNOWN, float h = 0.0f, float v = 0.0f);
	~SystemComponent();

	float getHealth();
	Ogre::String getName();
	SYSTEM_TYPE getType();
	float getValue();

	void addHealth(float h);
	void addValue(float v);

	void setHealth(float h);
	void setValue(float v);
	void damage(float d);

private:
	float health;
	SYSTEM_TYPE type;
	float value;

};

#endif // SYSTEM_COMPONENT_H