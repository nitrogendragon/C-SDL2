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
	//sprite values to use for initializing and updating if desired the height, width, starting rendering point
	int sRectH = 0, sRectW = 0, sRectX = 0, sRectY = 0;
	//scaling values
	float destHScale = 1.0, destWScale = 1.0;
public:
	//constructor
	SpriteComponent() = default;
	//create sprite component based path to texture img, starting img render points, number of horizontalxvertical pixels of source to render, and scaling
	SpriteComponent(const char* path, int x, int y, int srcRectH, int srcRectW, float destWScale, float destHScale)
	{
		//creates texture by loading our image using setTex function defined afterour function here
		setTex(path);
		sRectY = x;//setting x starting value render point of sprite img to our declared pixel point
		sRectY = y;//setting y starting value render point of sprite img to our declared pixel point
		sRectH = srcRectH;//source dimension height for GameObject texture
		sRectW = srcRectW;//source dimension width for GameObject texture
		destWScale = srcRect.w * destWScale;// window width dimension for GameObject texture
		destHScale = srcRect.h * destHScale;// window height dimension for GameObject texture
	}
	//set texture function taking in a path to a img so that we can set or swap textures
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		
		//setting x starting render point of sprite img to our declared pixel point
		srcRect.x = sRectX;
		//setting y starting render point of sprite img to our declared pixel point
		srcRect.y = sRectY;
		//source dimension height for GameObject texture
		srcRect.h = sRectH;
		//source dimension width for GameObject texture
		srcRect.w = sRectW;
		// window width scaling dimension for sprite
		destRect.w = int(srcRect.w * destWScale);
		// window height scaling dimension for sprite
		destRect.h = int(srcRect.h * destHScale);
	}

	void update() override
	{
		//sets our sprites x position to the x position of the entity
		destRect.x = position->x();
		//sets our sprites y position to the y position of the entity
		destRect.y = position->y();
	}
	//draws our sprite using the specified texture, pixel selection, and scaling
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

