#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
//creates a TileComponent
//constructor form is as follows (TileComponent(int x, int y, int id, int h, int w)
//x and y starting rendering points, w and h size parameters, id for identifying specific tiles
class TileComponent : public Component
{
public:
	//pointer of type TransformComponent 
	TransformComponent *transform;
	//pointer of type SpriteComponent
	SpriteComponent * sprite;
	//default constructor
	TileComponent() = default;
	//our SDL_Rect for our tilemap
	SDL_Rect tileRect;
	//integer for setting the id of the tile/tilemap
	int tileID;
	//file path... NOTE must be constant or visual studios will have a hissy fit
	const char* path;
	
	//set up tile position and dimensions...
	//Note: remember to update switch statement cases as more images are made
	TileComponent(int x, int y, int id, int h, int w)
	{
		
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		//configure this tiles id
		tileID = id;

		//switch statement case based on tileID to choose what tile png to load
		switch (tileID)
		{
		case 0:
			path = "Assets/simplewater_32x32.png";
			break;
		case 1:
			path = "Assets/simplegrass_32x32.png";
			break;
		case 2:
			path = "Assets/simpleground_32x32.png";
			break;
		case 3:
			path = "Assets/simplewater_32x32.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		//adding our tileRect information
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1, 1);
		//sets our transform to our entities address of its TransformComponent
		transform = &entity->getComponent<TransformComponent>();
		//adds spriteComponent to our entity
		entity->addComponent<SpriteComponent>(path);
		//sets our tileComponents sprite to our entities SpriteComponent sprite
		sprite = &entity->getComponent <SpriteComponent>();
	}
};