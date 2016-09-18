#include "IEntity.h"

void IEntity::Update()
{
	if (++_beat == _beatsPerMove)
	{
		PerformUpdate();
		_beat = 0;
	}
}

void IEntity::SetLevel(ILevel& level)
{
	_level = &level;
}

void IEntity::SetTarget(IEntity& target)
{
	_target = &target;
}

IEntity& IEntity::GetTarget() const
{
	return *_target;
}

ILevel& IEntity::GetLevel() const
{
	return *_level;
}

Point IEntity::GetPosition() const
{
	return _position;
}

void IEntity::SetPosition(Point point)
{
	_position = point;
}

int IEntity::GetHealth() const
{
	return _health;
}

void IEntity::SetHealth(int health)
{
	_health = health;
}

void IEntity::SetDamage(int damage)
{
	if (damage < 0)
	{
		damage = 0;
	}
	_damage = damage;
}

int IEntity::GetDamage() const
{
	return _damage;
}

bool IEntity::Damage(int amount)
{
	_health -= amount;
	return _health <= 0;
}

void IEntity::SetBeatsPerMove(int bpm)
{
	if (bpm < 1)
	{
		bpm = 1;
	}
	_beatsPerMove = bpm;
}

void IEntity::SetBeatOffset(int offset)
{
	_beat = offset;
}

int IEntity::GetPriority() const
{
	return _priority;
}

void IEntity::SetPriority(int priority)
{
	if (priority < 0)
	{
		priority = 0;
	}
	_priority = priority;
}
