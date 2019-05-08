#pragma once
#include <SDL.h>
//forward declaration so it knows there is a collidercomponent
class ColliderComponent;

class Collision
{
public:
	//collision function returning a bool for axis alligned bounding box collision detection taking in two SDL_Rects
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	//take in two collider objects and compare their information to see if they are colliding
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};