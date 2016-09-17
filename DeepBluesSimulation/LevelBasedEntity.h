#ifndef LEVEL_BASED_ENTITY_H
#define LEVEL_BASED_ENTITY_H

class ILevel;

#include "IEntity.h"

class LevelBasedEntity : public IEntity
{
public:
	void SetLevel(ILevel& level);
	ILevel& GetLevel() const;
private:
	ILevel* _level;
};

#endif