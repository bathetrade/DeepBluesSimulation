#ifndef DEEP_BLUES_LEVEL_H
#define DEEP_BLUES_LEVEL_H

#include "ILevel.h"
#include "ILogger.h"
#include "Pawn.h"

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
	void SetPawnHealth(int);
	//int GetBishopHealth() const;
	//int GetRookHealth() const;
	//int GetKnightHealth() const;
	//int GetQueenHealth() const;
	//int GetKingHealth() const;
	

private:

	//State
	std::vector<IEntity*> _entities;
	std::unordered_map<std::string, IEntity*> _spatialEntityMap;
	Point _minBounds;
	Point _maxBounds;
	ILogger& _logger;
	Pawn _pawns[8];

	//Health
	int _pawnHealth;
	int _bishopHealth;
	int _rookHealth;
	int _knightHealth;
	int _queenHealth;
	int _kingHealth;

	//Support
	void UpdateSpatialEntity(Point, Point);
	void InitializeHealth();
	void AddEntity(IEntity*, Point);

	//Creation
	void SetPawns();
	//void CreateBishops();
	//void CreateRooks();
	//void CreateKnights();
	//void CreateQueen();
	//void CreateKing();

};

#endif