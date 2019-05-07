#pragma once
#include "Collision.h"
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