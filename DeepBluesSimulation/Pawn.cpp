#include "Pawn.h"
#include "ILevel.h"

using namespace std;

Pawn::Pawn()
{
	SetPriority(1);
}

std::string Pawn::ToString() const
{
	return "Pawn";
}

vector<Point> Pawn::GeneratePossibleMoves() const
{
	auto currentPosition = GetPosition();
	vector<Point> possibleMoves = { currentPosition + Point(1,0) };
	return possibleMoves;
}

vector<Point> Pawn::GeneratePossibleAttacks() const
{
	vector<Point> attackPoints;
	auto position = GetPosition();

	attackPoints.push_back(position + Point(1, 1));
	attackPoints.push_back(position + Point(1, -1));

	return attackPoints;
}