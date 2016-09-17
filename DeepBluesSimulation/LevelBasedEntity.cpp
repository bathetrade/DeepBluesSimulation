#include "LevelBasedEntity.h"

void LevelBasedEntity::SetLevel(ILevel& level)
{
	_level = &level;
}

ILevel& LevelBasedEntity::GetLevel() const
{
	return *_level;
}