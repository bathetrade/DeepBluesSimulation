#include "Enemy.h"

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