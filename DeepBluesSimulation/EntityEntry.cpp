#include "EntityEntry.h"

EntityEntry::EntityEntry()
{
	Deleted = false;
	Entity = nullptr;
}

EntityEntry::EntityEntry(bool deleted, IEntity* entity)
{
	Deleted = deleted;
	Entity = entity;
}