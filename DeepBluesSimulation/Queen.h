#ifndef QUEEN_H
#define QUEEN_H

#include "Enemy.h"

class Queen : public Enemy
{
public:
	virtual std::string ToString() const override;
protected:
	virtual std::vector<Point> GeneratePossibleMoves() const override;
	virtual std::vector<Point> GeneratePossibleAttacks() const override;
};

#endif
