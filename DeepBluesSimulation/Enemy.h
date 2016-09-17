#ifndef ENEMY_H
#define ENEMY_H

#include "IEntity.h"
#include "ILevel.h"

class Enemy : public IEntity
{
public:
	void SetLevel(ILevel& level);
	void SetTarget(IEntity& target);
	ILevel& GetLevel() const;
	IEntity& GetTarget() const;
protected:
	Enemy();
private:
	ILevel* _level;
	IEntity* _target;
};
#endif