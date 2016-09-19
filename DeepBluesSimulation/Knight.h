#ifndef KNIGHT_H
#define KNIGHT_H

#include "Enemy.h"

class Knight : public Enemy
{
public:
	virtual std::string ToString() const override;
protected:
	virtual std::vector<Point> GeneratePossibleMoves() const override;
	virtual std::vector<Point> GeneratePossibleAttacks() const override;
};

#endif