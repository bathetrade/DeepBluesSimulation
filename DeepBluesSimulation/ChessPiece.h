#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "IEntity.h"
#include "ILevel.h"

class ChessPiece : public IEntity
{
protected:
	ChessPiece();
	void SetLevel(ILevel& level);
	void SetTarget(IEntity& target);
	ILevel& GetLevel() const;
	IEntity& GetTarget() const;
private:
	ILevel* _level;
	IEntity* _target;
};
#endif