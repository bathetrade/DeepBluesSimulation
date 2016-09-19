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
	virtual std::vector<Point> GeneratePossibleMoves() const override;
	virtual std::vector<Point> GeneratePossibleAttacks() const override;
};

#endif
