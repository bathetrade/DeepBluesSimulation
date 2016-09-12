#ifndef IWEAPON_H
#define IWEAPON_H

#include "IEntity.h"
#include "Point.h"
#include "ILevel.h"
#include "Direction.h"

class IWeapon
{
public:
	virtual bool Attack(IEntity&, ILevel&, Direction) = 0;
};

#endif