#ifndef ENEMY_H
#define ENEMY_H

#include "LevelBasedEntity.h"
#include <vector>

class Enemy : public LevelBasedEntity
{
public:
	void SetTarget(IEntity& target);
	IEntity& GetTarget() const;
protected:
	Enemy();
	virtual std::vector<Point> GeneratePossibleMoves() const = 0;
	virtual std::vector<Point> GeneratePossibleAttacks() const = 0;
	virtual void PerformUpdate() override;
private:
	IEntity* _target;

	bool TryAttackTarget();
	void TryMove();
};
#endif