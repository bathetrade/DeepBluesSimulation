#include "DeepBluesLevel.h"

#include <algorithm>
#include <sstream>

using namespace std;

DeepBluesLevel::DeepBluesLevel(ILogger& logger) : _logger(logger)
{
	_minBounds = Point(0, 0);
	_maxBounds = Point(8, 8);
}

void DeepBluesLevel::Initialize()
{
	//TODO: initialize board
}

IEntity& DeepBluesLevel::GetEntity(Point point) const
{
	return *(_spatialEntityMap.at(point.ToString()));
}

void DeepBluesLevel::RemoveEntity(IEntity& entity)
{
	//Remove from entity list
	auto entityIterator = std::find(_entities.begin(), _entities.end(), &entity);
	bool entityExists = entityIterator != _entities.end();
	if (entityExists)
	{
		_entities.erase(entityIterator);
	}

	//Remove from spatial map
	if (entityExists)
	{
		auto entityPointer = *entityIterator;
		auto entityPosition = entityPointer->GetPosition();
		auto spatialEntityIterator = _spatialEntityMap.find(entityPosition.ToString());
		bool entityMissingFromSpatialMap = spatialEntityIterator == _spatialEntityMap.end();

		//Log if entity is in list, but not in the spatial map (they should be consistent)
		if (entityMissingFromSpatialMap)
		{
			_logger.LogLine("Entity \"" + entityPointer->ToString() + "\" missing from spatial map!");
		}
		//Else, remove it
		else
		{
			_spatialEntityMap.erase(spatialEntityIterator);
		}
	}
}

void DeepBluesLevel::RequestMove(IEntity& entity, Point newPosition)
{
	//Make sure requested move is in bounds
	if (!InBounds(newPosition))
	{
		return;
	}

	//Update spatial map and entity with new position
	bool moveAllowed = HasEntity(newPosition) == false;
	if (moveAllowed)
	{
		auto currentPosition = entity.GetPosition();
		if (HasEntity(currentPosition))
		{
			UpdateSpatialEntity(currentPosition, newPosition);
			entity.SetPosition(newPosition);
		}
		else
		{
			stringstream errorMsg;
			errorMsg << "Warning: entity does not exist in spatial map. Entity: " << entity.ToString() << ". Current position: " << currentPosition.ToString() << ". New position: " << newPosition.ToString();
			_logger.LogLine(errorMsg.str());
		}
	}
}

void DeepBluesLevel::UpdateEntities()
{
	for_each(_entities.begin(), _entities.end(), [](IEntity* entity)
	{
		entity->Update();
	});
}

bool DeepBluesLevel::HasEntity(Point point) const
{
	return _spatialEntityMap.find(point.ToString()) != _spatialEntityMap.end();
}

bool DeepBluesLevel::InBounds(Point point) const
{
	return point.X >= _minBounds.X && point.Y >= _minBounds.Y && 
		point.X <= _maxBounds.X && point.Y <= _maxBounds.Y;
}

void DeepBluesLevel::UpdateSpatialEntity(Point oldPoint, Point newPoint)
{
	auto entityIterator = _spatialEntityMap.find(oldPoint.ToString());
	auto entityPointer = entityIterator->second;
	_spatialEntityMap.erase(entityIterator);
	_spatialEntityMap[newPoint.ToString()] = entityPointer;
}