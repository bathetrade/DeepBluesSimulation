#ifndef ILEVEL_H
#define ILEVEL_H

#include <vector>

#include "Point.h"

class IEntity;

class ILevel
{
public:
	virtual void Initialize() = 0;
	virtual IEntity* GetEntity(Point) const = 0;
	virtual void RemoveEntity(IEntity&) = 0;
	virtual void RequestMove(IEntity&, Point) = 0;
	virtual std::vector<Point> GetValidMoves(const std::vector<Point>&) = 0;
	virtual void UpdateEntities() = 0;
	virtual bool HasEntity(Point) const = 0;
	virtual bool InBounds(Point) const = 0;
};

#endif