#ifndef ENEMY_H
#define ENEMY_H

#include "LevelBasedEntity.h"

class Enemy : public LevelBasedEntity
{
public:
	void SetTarget(IEntity& target);
	IEntity& GetTarget() const;
protected:
	Enemy();
private:
	IEntity* _target;
};
#endif