#ifndef LASER_H
#define LASER_H

#include "physics_entity.h"

class Laser: public PhysicsEntity
{
public:
	Laser();
	~Laser();

	void Initialize(Entity* parent);

private:

};

#endif //LASER_H