#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::SetLevel(ILevel& level)
{
	_level = &level;
}

void Enemy::SetTarget(IEntity& target)
{
	_target = &target;
}

IEntity& Enemy::GetTarget() const
{
	return *_target;
}

ILevel& Enemy::GetLevel() const
{
	return *_level;
}