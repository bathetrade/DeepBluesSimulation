#include "Pawn.h"

using namespace std;

Pawn::Pawn()
{
	SetPriority(1);
}

std::string Pawn::ToString() const
{
	return "Pawn";
}

void Pawn::PerformUpdate()
{
	if (!TryAttackTarget())
	{
		TryMove();
	}
}

vector<Point> Pawn::GetAttackPoints() const
{
	vector<Point> attackPoints;
	auto position = GetPosition();

	attackPoints.push_back(position + Point(1, 1));
	attackPoints.push_back(position + Point(-1, 1));

	return attackPoints;
}

Point Pawn::GetMovePoint() const
{
	auto position = GetPosition();
	return position + Point(0, 1);
}

//TODO: generalize (logic is similar for all enemies)
bool Pawn::TryAttackTarget() const
{
	auto target = GetTarget();
	auto targetPosition = target.GetPosition();
	auto attackPoints = GetAttackPoints();
	auto attackPosition = find(attackPoints.begin(), attackPoints.end(), targetPosition);
	bool targetAttackable = attackPosition != attackPoints.end();

	if (targetAttackable)
	{
		target.Damage(GetDamage());
	}

	return targetAttackable;
}

void Pawn::TryMove()
{
	auto desiredPosition = GetMovePoint();
	auto level = GetLevel();
	level.RequestMove(*this, desiredPosition);
}