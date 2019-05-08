#pragma once
#include <SDL.h>

class Collision
{
public:
	//collision function returning a bool for axis alligned bounding box collision detection taking in two SDL_Rects
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};