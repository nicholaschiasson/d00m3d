#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

class SystemComponent
{
public:
	enum SYSTEM_TYPE
	{
		SYSTEM_NAVIGATIONAL,
	};

	SystemComponent();
	~SystemComponent();

private:
	SYSTEM_TYPE type;

};

#endif // SYSTEM_COMPONENT_H