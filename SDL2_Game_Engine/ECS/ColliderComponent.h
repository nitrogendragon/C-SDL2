#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"
using namespace std;
//colliderComponent is derived from our component class
//when calling the ColliderComponent Constructor it takes in (string t) for the tag name, and an int xpos,int ypos and int size var
class ColliderComponent : public Component
{
private:

public:
	//add area to represent collision area
	SDL_Rect collider;
	//add tags for collision detection and find out if its for example: play,er enemy, wall, etc
	string tag;


	SDL_Texture* tex;//texture for our collider
	SDL_Rect srcR, destR;//src and destination rects for our collider



	//collider needs access to transform component  so pointer to transform
	TransformComponent* transform;
	//constructor to set up tag for now
	ColliderComponent(string t)
	{
		tag = t;
	}
	//more complex constructor taking in position and size information
	ColliderComponent(string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
		
	}
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


		tex = TextureManager::LoadTexture("assets/boxcoltex_32x32.png");//loads our collider texture
		
		srcR = { 0,0,32,32 };//the origin point in upper left bounds 0,0 for starting the rect and its dims 32x32
		
		destR = { collider.x, collider.y, collider.w, collider.h };
		if (tag == "player")
		{
			collider.w = transform->width * transform->wScale / 3;
			//set up the height value of the box collider based on our transforms height
			collider.h = transform->height * transform->hScale / 3;
		}
		else if (tag == "projectile")
		{
			
			collider.w = transform->width * transform->wScale;
			//set up the height value of the box collider based on our transforms height
			collider.h = transform->height * transform->hScale;
		}
	}
	//taking care of position of hit/collider box updating
	void update() override
	{
		if (tag == "player")
		{
			
			//setting up our collider x position equal to our transforms position
			collider.x = static_cast<int>(transform->position.x+(transform->width*.365f * transform->wScale));
			//setting up our collider x position equal to our transforms position
			collider.y = static_cast<int>(transform->position.y+(transform->height*.675f * transform->hScale));
			//set up the width value of the box collider based on our transforms width
			
			destR = { collider.x, collider.y, collider.w, collider.h };//renders box over player
			
		}
		else if (tag == "projectile")
		{
			//setting up our collider x position equal to our transforms position
			collider.x = static_cast<int>(transform->position.x);
			//setting up our collider x position equal to our transforms position
			collider.y = static_cast<int>(transform->position.y);
			destR = { collider.x, collider.y, collider.w, collider.h };//renders box over player
		}
		
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;

	}

	void draw() override
	{
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};
