#ifndef IENTITY_H
#define IENTITY_H

#include "Point.h"

class IEntity
{
public:
	virtual void Update();
	virtual std::string ToString() const = 0;

	Point GetPosition() const;
	void SetPosition(Point);
	int GetHealth() const;
	void SetHealth(int);
	bool Damage(int amount);
	void SetBeatsPerMove(int);
	void SetBeatOffset(int);
	bool TimeToMove();

protected:
	virtual void PerformUpdate() = 0;

private:
	int _health;
	int _beat;
	int _beatsPerMove;
	Point _position;
};

#endif