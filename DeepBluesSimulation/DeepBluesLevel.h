#ifndef DEEP_BLUES_LEVEL_H
#define DEEP_BLUES_LEVEL_H

#include "ILevel.h"
#include "ILogger.h"
#include "Pawn.h"

#include <vector>
#include <memory>

class IEntity;
class Pawn;
class Cadence;

class DeepBluesLevel : public ILevel
{
public:
	
	//Constructors
	DeepBluesLevel(Cadence&, ILogger&);

	//ILevel
	virtual void Initialize() override;
	virtual IEntity* GetEntity(Point) const override;
	virtual void RemoveEntity(IEntity&) override;
	virtual void RequestMove(IEntity&, Point) override;
	virtual std::vector<Point> GetValidMoves(const std::vector<Point>&) override;
	virtual void UpdateEntities() override;
	virtual bool HasEntity(Point) const override;
	virtual bool InBounds(Point) const override;

	//Level
	void PrintBoard() const;

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
	std::vector<std::vector<IEntity*>> _board;
	std::vector<IEntity*> _entities;
	bool _removeDeletedEntities;
	ILogger& _logger;
	Cadence& _cadence;
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
	void UpdateEntityPosition(IEntity*, Point);
	void InitializeHealth();
	void InitializeDamage();
	void InitializeBoard();
	void AddEntity(IEntity*);
	bool MarkEntityForDeletionIfItExists(IEntity* entity);
	void CleanListIfNecessary();
	size_t GetMaxStringWidth() const;

	//Creation
	void SetCadence();
	void SetPawns();
	//void CreateBishops();
	//void CreateRooks();
	//void CreateKnights();
	//void CreateQueen();
	//void CreateKing();

};

#endif