#ifndef ENTITY_ENTRY_H
#define ENTITY_ENTRY_H

#include "IEntity.h"

struct EntityEntry
{
	EntityEntry();
	EntityEntry(bool, IEntity*);
	bool Deleted;
	IEntity* Entity;
};

#endif