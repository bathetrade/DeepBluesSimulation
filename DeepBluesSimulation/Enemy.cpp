#include "Enemy.h"
#include "PointMath.h"
#include "ILevel.h"
#include <numeric>

using namespace std;

void Enemy::SetTarget(IEntity& target)
{
	_target = &target;
}

IEntity& Enemy::GetTarget() const
{
	return *_target;
}

void Enemy::PerformUpdate()
{
	if (!TryAttackTarget())
	{
		TryMove();
	}
}

bool Enemy::TryAttackTarget()
{
	//Can the target be attacked?
	auto targetPosition = _target->GetPosition();
	auto attackPoints = GeneratePossibleAttacks();
	auto attackPoint = find(attackPoints.begin(), attackPoints.end(), targetPosition);
	bool targetAttackable = attackPoint != attackPoints.end();

	if (targetAttackable)
	{
		_target->Damage(GetDamage());
	}

	return targetAttackable;
}

void Enemy::TryMove()
{
	//Initialize
	ILevel& level = GetLevel();
	auto targetPosition = _target->GetPosition();
	auto currentPosition = GetPosition();

	//Get valid moves
	auto movePoints = level.GetValidMoves(GeneratePossibleMoves());

	//Calculate current distance to target
	auto bestMove = movePoints.end();
	int minimumDistanceToTarget = GetDistance(currentPosition, targetPosition);

	//Find first move that is closer than the current move (if any)
	for (auto it = movePoints.begin(); it != movePoints.end(); ++it)
	{
		int distanceToTarget = GetDistance(*it, targetPosition);
		if (distanceToTarget < minimumDistanceToTarget)
		{
			minimumDistanceToTarget = distanceToTarget;
			bestMove = it;
		}
	}

	//Move if there is a better move
	bool betterMoveFound = (bestMove != movePoints.end());
	if (betterMoveFound)
	{
		level.RequestMove(*this, *bestMove);
	}
}
