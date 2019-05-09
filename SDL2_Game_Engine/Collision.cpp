#pragma once
#include "Collision.h"
#include <iostream>
#include "ECS\ColliderComponent.h"
using namespace std;
//collision class implementation checking via AABB conditions for collision and returning a boolean based on if we meet the conditions or not
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if
		(
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.y
			)
	{
		
		return true;

	}
	
	return false;
}
//checks for collisions AABB style by passing in colliders
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//make sure we aren't hitting ourselves
		if (colA.tag != colB.tag) {
			//let us know who hit who
			cout << colA.tag << " hit: " << colB.tag << endl;
			//we hit something
			return true;
		}
		else {
			//we hit ourselves so no collision
			return false;
		}
	}
	else
	{
		//do nothing
		return false;
	}
}