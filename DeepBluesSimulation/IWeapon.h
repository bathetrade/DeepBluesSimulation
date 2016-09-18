#ifndef IWEAPON_H
#define IWEAPON_H

#include "Direction.h"

class IEntity;
class ILevel;

class IWeapon
{
public:
	virtual ~IWeapon() {}
	virtual bool Attack(IEntity&, ILevel&, Direction) = 0;
};

#endif