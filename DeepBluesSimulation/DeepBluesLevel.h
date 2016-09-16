#ifndef DEEP_BLUES_LEVEL_H
#define DEEP_BLUES_LEVEL_H

#include "ILevel.h"
#include "ILogger.h"
#include "Pawn.h"
#include "EntityEntry.h"
#include "Cadence.h"

#include <vector>
#include <unordered_map>
#include <memory>

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

protected:
	//Health
	void SetPawnHealth(int);
	void SetBishopHealth(int);
	void SetRookHealth(int);
	void SetKnightHealth(int);
	void SetQueenHealth(int);
	void SetKingHealth(int);

	//Damage
	void SetPawnDamage(int);
	void SetBishopDamage(int);
	void SetRookDamage(int);
	void SetKnightDamage(int);
	void SetQueenDamage(int);
	void SetKingDamage(int);

private:

	//State
	std::vector<EntityEntry> _entities;
	std::unordered_map<std::string, IEntity*> _spatialEntityMap;
	bool _removeDeletedEntities;
	Point _minBounds;
	Point _maxBounds;
	ILogger& _logger;
	Cadence _cadence;
	Pawn _pawns[8];

	//Health
	int _pawnHealth;
	int _bishopHealth;
	int _rookHealth;
	int _knightHealth;
	int _queenHealth;
	int _kingHealth;

	//Damage
	int _pawnDamage;
	int _bishopDamage;
	int _rookDamage;
	int _knightDamage;
	int _queenDamage;
	int _kingDamage;

	//Support
	void UpdateSpatialEntity(Point, Point);
	void InitializeHealth();
	void InitializeDamage();
	void AddEntity(IEntity*, Point);
	bool MarkEntityForDeletionIfItExists(IEntity* entity);
	void CleanListIfNecessary();

	//Creation
	void SetPawns();
	//void CreateBishops();
	//void CreateRooks();
	//void CreateKnights();
	//void CreateQueen();
	//void CreateKing();

};

#endif