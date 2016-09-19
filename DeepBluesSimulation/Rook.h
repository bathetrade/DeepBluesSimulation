#ifndef ROOK_H
#define ROOK_H

#include "Enemy.h"

class Rook : public Enemy
{
public:
	virtual std::string ToString() const override;
protected:
	virtual std::vector<Point> GeneratePossibleMoves() const override;
	virtual std::vector<Point> GeneratePossibleAttacks() const override;
};

#endif