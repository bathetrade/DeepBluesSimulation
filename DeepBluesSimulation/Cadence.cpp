#include "Cadence.h"
#include "Constants.h"
#include "ILevel.h"
#include <iostream>

/**********************************************************/
/***************** Constructors ***************************/
/**********************************************************/
Cadence::Cadence()
{
	SetHealth(Constants::CadenceHealthDefault);
	SetPriority(0);
}

/**********************************************************/
/***************** IEntity ********************************/
/**********************************************************/
void Cadence::Update()
{
	if (_moveSet)
	{
		//Try attacking. If the attack failed, try moving.
		auto desiredPosition = GetDesiredMovePoint();
		ILevel& level = GetLevel();
		if (_weapon == nullptr || !_weapon->Attack(*this, level, _moveDirection))
		{
			level.RequestMove(*this, desiredPosition);
		}
		_moveSet = false;
	}
}

std::string Cadence::ToString() const
{
	return "Cadence";
}

void Cadence::PerformUpdate()
{
}

/**********************************************************/
/***************** Cadence ********************************/
/**********************************************************/
void Cadence::SetMove(Direction direction)
{
	_moveSet = true;
	_moveDirection = direction;
}

void Cadence::EquipWeapon(IWeapon* weapon)
{
	_weapon.reset(weapon);
}

/**********************************************************/
/***************** Support ********************************/
/**********************************************************/
Point Cadence::GetDesiredMovePoint() const
{
	switch (_moveDirection)
	{
		case Direction::UP:
			return GetPosition() + Point(-1, 0);

		case Direction::RIGHT:
			return GetPosition() + Point(0, 1);

		case Direction::DOWN:
			return GetPosition() + Point(1, 0);

		case Direction::LEFT:
			return GetPosition() + Point(0, -1);

		default:
			throw std::runtime_error("Unimplemented direction");
	}
}
