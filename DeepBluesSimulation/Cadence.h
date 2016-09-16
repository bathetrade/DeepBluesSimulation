#ifndef CADENCE_H
#define CADENCE_H

#include "IEntity.h"
#include "Direction.h"
#include "Point.h"
#include "ILevel.h"
#include "IWeapon.h"

#include <memory>

class Cadence : public IEntity
{
public:
	//Constructors
	Cadence(ILevel&);

	//IEntity
	virtual void Update() override;
	virtual std::string ToString() const override;

	//Cadence
	void SetMove(Direction);
	void EquipWeapon(IWeapon* weapon);

protected:
	//IEntity
	virtual void PerformUpdate() override;

private:
	//State
	Point _position;
	bool _moveSet;
	Direction _moveDirection;
	ILevel& _level;
	std::unique_ptr<IWeapon> _weapon;

	//Support
	Point GetDesiredMovePoint() const;
};

#endif