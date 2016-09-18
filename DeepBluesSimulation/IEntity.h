#ifndef IENTITY_H
#define IENTITY_H

#include "Point.h"

class ILevel;

class IEntity
{
public:
	virtual void Update();
	virtual std::string ToString() const = 0;

	void SetLevel(ILevel& level);
	void SetTarget(IEntity& target);
	ILevel& GetLevel() const;
	IEntity& GetTarget() const;
	Point GetPosition() const;
	void SetPosition(Point);
	int GetHealth() const;
	void SetHealth(int);
	void SetDamage(int);
	int GetDamage() const;
	bool Damage(int amount);
	void SetBeatsPerMove(int);
	void SetBeatOffset(int);
	int GetPriority() const;

protected:
	virtual void PerformUpdate() = 0;
	void SetPriority(int);

private:
	int _health;
	int _beat;
	int _beatsPerMove;
	int _priority;
	int _damage;
	Point _position;
	ILevel* _level;
	IEntity* _target;
};

#endif