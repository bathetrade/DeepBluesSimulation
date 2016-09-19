#include "Rook.h"

std::string Rook::ToString() const
{
	return "Rook";
}

//TODO: verify order of move directions
std::vector<Point> Rook::GeneratePossibleMoves() const
{
	auto currentPosition = GetPosition();
	return{ currentPosition + Point(0, 1),
			currentPosition + Point(0, -1),
			currentPosition + Point(1, 0),
			currentPosition + Point(-1, 0) };
}

std::vector<Point> Rook::GeneratePossibleAttacks() const
{
	return GeneratePossibleAttacks();
}
