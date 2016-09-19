#ifndef CADENCE_H
#define CADENCE_H

#include "LevelBasedEntity.h"
#include "Direction.h"
#include "IWeapon.h"
#include <memory>

class Cadence : public LevelBasedEntity
{
public:
	//Constructors
	Cadence();

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
	bool _moveSet;
	Direction _moveDirection;
	std::unique_ptr<IWeapon> _weapon;

	//Support
	Point GetDesiredMovePoint() const;
};

#endif