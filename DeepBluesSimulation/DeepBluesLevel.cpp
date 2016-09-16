#include "DeepBluesLevel.h"
#include "DeepBluesHealth.h"
#include "DeepBluesDamage.h"

#include <algorithm>
#include <sstream>

using namespace std;

DeepBluesLevel::DeepBluesLevel(ILogger& logger) : _logger(logger), _cadence(*this)
{
	_minBounds = Point(0, 0);
	_maxBounds = Point(8, 8);
	InitializeHealth();
	InitializeDamage();
}

//TODO: make idempotent
void DeepBluesLevel::Initialize()
{
	SetPawns();
	//CreateBishops();
	//CreateRooks();
	//CreateKnights();
	//CreateQueen();
	//CreateKing();
}

IEntity& DeepBluesLevel::GetEntity(Point point) const
{
	return *(_spatialEntityMap.at(point.ToString()));
}

void DeepBluesLevel::RemoveEntity(IEntity& entity)
{
	bool entityExists = MarkEntityForDeletionIfItExists(&entity);

	//Remove from spatial map (we can remove directly, since no one iterates over the spatial map)
	if (entityExists)
	{
		auto entityPosition = entity.GetPosition();
		auto spatialEntityIterator = _spatialEntityMap.find(entityPosition.ToString());
		bool entityMissingFromSpatialMap = spatialEntityIterator == _spatialEntityMap.end();

		//Log if entity is in list, but not in the spatial map (they should be consistent)
		if (entityMissingFromSpatialMap)
		{
			_logger.LogLine("Entity \"" + entity.ToString() + "\" missing from spatial map!");
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
	bool positionOpen = HasEntity(newPosition) == false;
	if (positionOpen)
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
	//Update non-deleted entities
	for_each(_entities.begin(), _entities.end(), [](EntityEntry& entry)
	{
		if (entry.Deleted == false)
		{
			entry.Entity->Update();
		}
	});

	CleanListIfNecessary();
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

void DeepBluesLevel::SetPawnHealth(int health)
{
	_pawnHealth = health;
}

void DeepBluesLevel::SetBishopHealth(int health)
{
	_bishopHealth = health;
}

void DeepBluesLevel::SetRookHealth(int health)
{
	_rookHealth = health;
}

void DeepBluesLevel::SetKnightHealth(int health)
{
	_knightHealth = health;
}

void DeepBluesLevel::SetQueenHealth(int health)
{
	_queenHealth = health;
}

void DeepBluesLevel::SetKingHealth(int health)
{
	_kingHealth = health;
}


void DeepBluesLevel::SetPawnDamage(int damage)
{
	_pawnDamage = damage;
}

void DeepBluesLevel::SetBishopDamage(int damage)
{
	_bishopDamage = damage;
}

void DeepBluesLevel::SetRookDamage(int damage)
{
	_rookDamage = damage;
}

void DeepBluesLevel::SetKnightDamage(int damage)
{
	_knightDamage = damage;
}

void DeepBluesLevel::SetQueenDamage(int damage)
{
	_queenDamage = damage;
}

void DeepBluesLevel::SetKingDamage(int damage)
{
	_kingDamage = damage;
}

void DeepBluesLevel::UpdateSpatialEntity(Point oldPoint, Point newPoint)
{
	auto entityIterator = _spatialEntityMap.find(oldPoint.ToString());
	auto entityPointer = entityIterator->second;
	_spatialEntityMap.erase(entityIterator);
	_spatialEntityMap[newPoint.ToString()] = entityPointer;
}

void DeepBluesLevel::InitializeHealth()
{
	SetPawnHealth(DeepBluesHealth::DeepBlues1PawnHealth);
	SetBishopHealth(DeepBluesHealth::DeepBlues1BishopHealth);
	SetRookHealth(DeepBluesHealth::DeepBlues1RookHealth);
	SetKnightHealth(DeepBluesHealth::DeepBlues1KnightHealth);
	SetQueenHealth(DeepBluesHealth::DeepBlues1QueenHealth);
	SetKingHealth(DeepBluesHealth::DeepBlues1KingHealth);
}

void DeepBluesLevel::InitializeDamage()
{
	SetPawnDamage(DeepBluesDamage::DeepBlues1PawnDamage);
	SetBishopDamage(DeepBluesDamage::DeepBlues1BishopDamage);
	SetRookDamage(DeepBluesDamage::DeepBlues1RookDamage);
	SetKnightDamage(DeepBluesDamage::DeepBlues1KnightDamage);
	SetQueenDamage(DeepBluesDamage::DeepBlues1QueenDamage);
	SetKingDamage(DeepBluesDamage::DeepBlues1KingDamage);
}

void DeepBluesLevel::AddEntity(IEntity* entity, Point point)
{
	_entities.emplace_back(EntityEntry(false, entity));
	_spatialEntityMap[point.ToString()] = entity;
}

bool DeepBluesLevel::MarkEntityForDeletionIfItExists(IEntity* entity)
{
	//Mark entity for deletion, if it exists and isn't already marked
	auto entityIterator = std::find_if(_entities.begin(), _entities.end(), [&](EntityEntry entry)
	{
		return (entry.Entity == entity) && (entry.Deleted == false);
	});

	//Does the entity exist?
	bool entityExists = entityIterator != _entities.end();

	//Set the flag that signals the list needs to be cleaned up at a later time (we can't just delete the entity, since someone may be iterating over the entities list; e.g., see UpdateEntities())
	if (entityExists)
	{
		entityIterator->Deleted = true;
		_removeDeletedEntities = true;
	}

	return entityExists;
}

void DeepBluesLevel::CleanListIfNecessary()
{
	if (_removeDeletedEntities)
	{
		auto it = _entities.begin();
		while (it != _entities.end())
		{
			if (it->Deleted == true)
			{
				it = _entities.erase(it);
			}
		}
	}
}

void DeepBluesLevel::SetPawns()
{
	for (int col = 0; col < 8; ++col)
	{
		auto position = Point(1, col);
		_pawns[col].SetHealth(_pawnHealth);
		_pawns[col].SetDamage(_pawnDamage);
		_pawns[col].SetPosition(position);
		_pawns[col].SetLevel(*this);
		_pawns[col].SetTarget(_cadence);
		AddEntity(_pawns + col, position);
	}
}