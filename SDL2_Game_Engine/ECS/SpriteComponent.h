#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
class SpriteComponent: public Component
{
private:
	//reference to the position of the sprite
	TransformComponent *transform;
	//texture for the sprite 
	SDL_Texture *texture;
	//rects for sizing and scaling sprite
	SDL_Rect srcRect, destRect;
	
public:
	//constructor
	SpriteComponent() = default;
	//for if we want to use TransformComponent to set up scaling and such
	
	//create sprite component based path to texture img, starting img render points, number of horizontalxvertical pixels of source to render, and scaling
	SpriteComponent(const char* path)
	{
		//creates texture by loading our image using setTex function defined after our function here
		setTex(path);
	
	}

	//deconstructor to destroy texture when gone
	~SpriteComponent()
	{
		//destroying our texture
		SDL_DestroyTexture(texture);
	}

	//set texture function taking in a path to a img so that we can set or swap textures
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		//sets our TransformComponent transform to our entities TransformComponent
		transform = &entity->getComponent<TransformComponent>();
		//we want to draw the whole image so we start from the beginning aka the top left of the img
		srcRect.x = srcRect.y = 0;
		//set our width to our transforms width which we already defined when we added our TransformComponent
		srcRect.w = transform->width;
		//set our height to our transforms width which we already defined when we added our TransformComponent
		srcRect.h = transform->height;
	}

	void update() override
	{
		//sets our sprites x position to the x position of the entity
		destRect.x = static_cast<int>(transform->position.x);
		//sets our sprites y position to the y position of the entity
		destRect.y = static_cast<int>(transform->position.y);
		//set up our scaled sprite img 
		destRect.w = transform->width * transform->wScale;
		//set up our scaled sprite img
		destRect.h = transform->height * transform->hScale;
	}
	//draws our sprite using the specified texture, pixel selection, and scaling
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

