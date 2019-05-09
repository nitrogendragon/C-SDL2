#include "ECS.h"
//sets the Entities groupBitset to true for the mGroup and adds it(this) to the group
void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}