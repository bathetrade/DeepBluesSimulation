#include "Enemy.h"
#include "PointMath.h"

#include <numeric>

using namespace std;

Enemy::Enemy()
{
}

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
	auto targetPosition = _target->GetPosition();
	auto currentPosition = GetPosition();
	auto movePoints = GeneratePossibleAttacks();
	auto bestMove = movePoints.end();
	int distanceToTarget = GetDistance(currentPosition, targetPosition);

	//Find first move that is closer than the current move
	for (auto it = movePoints.begin(); it != movePoints.end(); ++it)
	{
		if (GetDistance(*it, targetPosition) < distanceToTarget)
		{
			bestMove = it;
		}
	}
}
