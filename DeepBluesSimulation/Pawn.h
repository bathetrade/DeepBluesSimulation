#ifndef PAWN_H
#define PAWN_H

#include "Enemy.h"

#include <vector>

class Pawn : public Enemy
{
public:
	Pawn();
	virtual std::string ToString() const override;
protected:
	virtual void PerformUpdate() override;
private:
	std::vector<Point> GetAttackPoints() const;
	Point GetMovePoint() const;
	bool TryAttackTarget() const;
	void TryMove();
};

#endif
