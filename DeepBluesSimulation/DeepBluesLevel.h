#ifndef DEEP_BLUES_LEVEL_H
#define DEEP_BLUES_LEVEL_H

#include "ILevel.h"
#include "ILogger.h"

#include <vector>
#include <unordered_map>

class DeepBluesLevel : ILevel
{
public:
	
	//Constructors
	DeepBluesLevel(ILogger&);

	//ILevel
	virtual void Initialize() override;
	virtual IEntity& GetEntity(Point) const override;
	virtual void RemoveEntity(IEntity&) override;
	virtual void RequestMove(IEntity&, Point) override;
	virtual void UpdateEntities() override;
	virtual bool HasEntity(Point) const override;
	virtual bool InBounds(Point) const override;

private:

	//State
	std::vector<IEntity*> _entities;
	std::unordered_map<std::string, IEntity*> _spatialEntityMap;
	Point _minBounds;
	Point _maxBounds;
	ILogger& _logger;

	//Support
	void UpdateSpatialEntity(Point, Point);
};

#endif