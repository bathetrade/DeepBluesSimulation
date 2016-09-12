#ifndef PAWN_H
#define PAWN_H

#include "IEntity.h"
#include "ILevel.h"

class Pawn : IEntity
{
public:
	Pawn(ILevel&, const IEntity&);
	virtual std::string ToString() const override;
protected:
	virtual void PerformUpdate() override;
private:
	ILevel& _level;
	const IEntity& _target;
};

#endif
