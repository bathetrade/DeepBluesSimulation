#include "ChessPiece.h"

ChessPiece::ChessPiece()
{
}

void ChessPiece::SetLevel(ILevel& level)
{
	_level = &level;
}

void ChessPiece::SetTarget(IEntity& target)
{
	_target = &target;
}

IEntity& ChessPiece::GetTarget() const
{
	return *_target;
}

ILevel& ChessPiece::GetLevel() const
{
	return *_level;
}