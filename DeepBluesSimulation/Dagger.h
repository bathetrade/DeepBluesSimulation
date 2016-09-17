#ifndef DAGGER_H
#define DAGGER_H

#include "IWeapon.h"

class Dagger : public IWeapon
{
public:
	virtual bool Attack(IEntity&, ILevel&, Direction direction) override;

private:
	Point GetAttackedPosition(Point, Direction) const;
};

#endif