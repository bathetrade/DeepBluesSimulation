#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "IEntity.h"
#include "ILevel.h"

class ChessPiece : public IEntity
{
public:
	void SetLevel(ILevel& level);
	void SetTarget(IEntity& target);
	ILevel& GetLevel() const;
	IEntity& GetTarget() const;
protected:
	ChessPiece();
private:
	ILevel* _level;
	IEntity* _target;
};
#endif