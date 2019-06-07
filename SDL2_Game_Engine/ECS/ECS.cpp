#include "ECS.h"
//sets the Entities groupBitset to true for the mGroup and adds it(this) to the group
void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

//every frame move through our entities and remove the ones that aren't there(no longer active) from our groups
void Manager::refresh()
{
	for (auto i(0u); i < maxGroups; i++)
	{
		auto& v(groupedEntities[i]);
		v.erase
		(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
		{
			return !mEntity->isActive() || !mEntity->hasGroup(i);
		}),
			std::end(v));
	}
	
	cout << entities.size() << endl;
	
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity> &mEntity)
	{
		
		return !mEntity->isActive();
		
		
	}),
		end(entities));



}