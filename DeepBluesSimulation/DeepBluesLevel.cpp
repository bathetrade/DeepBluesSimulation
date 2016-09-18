#include "DeepBluesLevel.h"
#include "DeepBluesHealth.h"
#include "DeepBluesDamage.h"
#include "Cadence.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

DeepBluesLevel::DeepBluesLevel(Cadence& cadence, ILogger& logger) : _cadence(cadence), _logger(logger)
{
	InitializeHealth();
	InitializeDamage();
	InitializeBoard();
}

//TODO: make idempotent
void DeepBluesLevel::Initialize()
{
	SetCadence();
	SetPawns();
	//CreateBishops();
	//CreateRooks();
	//CreateKnights();
	//CreateQueen();
	//CreateKing();
}

IEntity* DeepBluesLevel::GetEntity(Point point) const
{
	if (!InBounds(point))
	{
		return nullptr;
	}
	return _board[point.X][point.Y];
}

void DeepBluesLevel::RemoveEntity(IEntity& entity)
{
	MarkEntityForDeletionIfItExists(&entity);
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
		UpdateEntityPosition(&entity, newPosition);
	}
}

void DeepBluesLevel::UpdateEntities()
{
	//Update non-deleted entities
	for_each(_entities.begin(), _entities.end(), [](IEntity* entity)
	{
		if (entity != nullptr)
		{
			entity->Update();
		}
	});

	CleanListIfNecessary();
}

bool DeepBluesLevel::HasEntity(Point point) const
{
	return GetEntity(point) != nullptr;
}

bool DeepBluesLevel::InBounds(Point point) const
{
	//8x8 chessboard
	return point.X >= 0 && point.Y >= 0 &&
		point.X < 8 && point.Y < 8;
}

void DeepBluesLevel::PrintBoard() const
{
	size_t columnWidth = GetMaxStringWidth() + 1;
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			auto entity = _board[row][col];
			if (entity != nullptr)
			{
				cout << setw(columnWidth) << entity->ToString();
			}
			else
			{
				cout << setw(columnWidth) << "x";
			}
		}
		cout << endl;
	}
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

void DeepBluesLevel::UpdateEntityPosition(IEntity* entity, Point newPoint)
{
	auto currentPoint = entity->GetPosition();
	if (HasEntity(currentPoint))
	{
		_board[currentPoint.X][currentPoint.Y] = nullptr;
		_board[newPoint.X][newPoint.Y] = entity;
		entity->SetPosition(newPoint);
	}
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

void DeepBluesLevel::InitializeBoard()
{
	_board.resize(8);
	for (int row = 0; row < 8; ++row)
	{
		_board[row].resize(8);
	}
}

void DeepBluesLevel::AddEntity(IEntity* entity)
{
	//Add to board
	auto position = entity->GetPosition();
	_board[position.X][position.Y] = entity;

	//Add to list
	_entities.push_back(entity);
}

bool DeepBluesLevel::MarkEntityForDeletionIfItExists(IEntity* entity)
{
	//Find entity
	auto entityIterator = std::find_if(_entities.begin(), _entities.end(), [&](IEntity* e)
	{
		return e == entity;
	});

	bool entityExists = entityIterator != _entities.end();

	if (entityExists)
	{
		//Clear entity in board
		auto position = (*entityIterator)->GetPosition();
		_board[position.X][position.Y] = nullptr;

		//Clear entity in list
		*entityIterator = nullptr;

		//Set flag
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
			if (*it == nullptr)
			{
				it = _entities.erase(it);
			}
			else
			{
				++it;
			}
		}
		_removeDeletedEntities = false;
	}
}

size_t DeepBluesLevel::GetMaxStringWidth() const
{
	size_t width = 0;
	for (auto entity : _entities)
	{
		if (entity != nullptr)
		{
			width = max(width, entity->ToString().size());
		}
	}
	return width;
}

void DeepBluesLevel::SetCadence()
{
	_cadence.SetLevel(*this);
	AddEntity(&_cadence);
}

void DeepBluesLevel::SetPawns()
{
	for (int i = 0; i < 1; ++i)
	{
		auto position = Point(1, i);
		_pawns[i].SetHealth(_pawnHealth);
		_pawns[i].SetDamage(_pawnDamage);
		_pawns[i].SetPosition(position);
		_pawns[i].SetLevel(*this);
		_pawns[i].SetTarget(_cadence);
		_pawns[i].SetBeatsPerMove(2);
		AddEntity(&_pawns[i]);
	}
}