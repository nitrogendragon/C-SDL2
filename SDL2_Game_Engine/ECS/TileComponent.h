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

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;


	TileComponent() = default;
	
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	//set up tile position and dimensions...
	//Note: remember to update switch statement cases as more images are made
	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 32;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};