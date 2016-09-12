#include "IEntity.h"

void IEntity::Update()
{
	if (_beat == _beatsPerMove)
	{
		PerformUpdate();
		_beat = 0;
	}
	else
	{
		++_beat;
	}
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

bool IEntity::Damage(int amount)
{
	_health -= amount;
	return _health <= 0;
}

void IEntity::SetBeatsPerMove(int bpm)
{
	_beatsPerMove = bpm;
}

void IEntity::SetBeatOffset(int offset)
{
	_beat = offset;
}
