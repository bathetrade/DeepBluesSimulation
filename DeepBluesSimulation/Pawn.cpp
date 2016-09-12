#include "Pawn.h"

Pawn::Pawn(ILevel& level, const IEntity& target) : _level(level), _target(target)
{
}

std::string Pawn::ToString() const
{
	return "Pawn";
}

void Pawn::PerformUpdate()
{

}