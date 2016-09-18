#include "Dagger.h"
#include "WeaponDamage.h"
#include "IEntity.h"
#include "ILevel.h"

bool Dagger::Attack(IEntity& attacker, ILevel& level, Direction direction)
{
	auto attackerPosition = attacker.GetPosition();
	auto attackedPosition = GetAttackedPosition(attackerPosition, direction);

	//Attack (and possibly kill) entity, if there's one in the attacked position
	if (level.HasEntity(attackedPosition))
	{
		IEntity* entity = level.GetEntity(attackedPosition);
		bool killed = entity->Damage(WeaponDamage::DaggerDamage);
		if (killed)
		{
			level.RemoveEntity(*entity);
		}
		return true;
	}
	return false;
}

Point Dagger::GetAttackedPosition(Point point, Direction direction) const
{
	switch (direction)
	{
		case Direction::UP:
			return point + Point(-1, 0);

		case Direction::RIGHT:
			return point + Point(0, 1);

		case Direction::DOWN:
			return point + Point(1, 0);

		case Direction::LEFT:
			return point + Point(0, -1);

		default:
			throw std::runtime_error("Unimplemented direction");
	}
}