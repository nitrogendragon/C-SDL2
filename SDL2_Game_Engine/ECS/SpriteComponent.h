#pragma once
#include "Components.h"
#include "SDL.h"
class SpriteComponent: public Component
{
private:
	//reference to the position of the sprite
	PositionComponent *position;
	//texture for the sprite 
	SDL_Texture *texture;
	//rects for sizing and scaling sprite
	SDL_Rect srcRect, destRect;
public:
	//constructor
	SpriteComponent() = default;
	//path to the texture or filename of the texture to be used
	SpriteComponent(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		//starting point for where to begin rendering image from usually 0,0
		srcRect.x = srcRect.y = 0;
		//number of pixels horizontally and vertically to include from src image
		srcRect.w = srcRect.h = 32;
		//double scale
		destRect.w = destRect.h = 64;
	}

	void update() override
	{
		//sets our sprites x position to the x position of the entity
		destRect.x = position->x();
		//sets our sprites y position to the y position of the entity
		destRect.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

