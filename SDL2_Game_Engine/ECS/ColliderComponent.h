#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
using namespace std;
//colliderComponent is derived from our component class
class ColliderComponent : public Component
{
	//add area to represent collision area
	SDL_Rect collider;
	//add tags for collision detection and find out if its for example: play,er enemy, wall, etc
	string tag;

	//collider needs access to transform component  so pointer to transform
	TransformComponent* transform;
	//override our initializer function
	void init() override
	{
		//if we dont already have the TransformComponent we will add one since this won't work without it
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent <TransformComponent>();
		}
		//set transform equal to the entities adress of its TransformComponent, so basically wherever the transformcomponent is stored, that is where our transform will be working in
		transform = &entity->getComponent<TransformComponent>();
	}
	//taking care of position of hit/collider box updating
	void update() override
	{
		//setting up our collider x position equal to our transforms position
		collider.x = transform->position.x;
		//setting up our collider x position equal to our transforms position
		collider.y = transform->position.y;
		//set up the y value of the box collider based on our transforms width
		collider.w = transform->width * transform->wScale;
		//set up the x value of the box collider based on our transforms height
		collider.x = transform->height * transform->hScale;

	}
};
