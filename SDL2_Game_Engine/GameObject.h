#pragma once
#include "Game.h"
class GameObject
{
public:
	// creates and renders our gameobject based off the texturesheet, positions, and given dimensions / scaling based off of source dimensions
	GameObject(const char* texturesheet, int x, int y,int srcRectH, int srcRectW, float destRectH, float destRectW);	
	~GameObject();//destructor for GameObject

	void Update();//update function for updating gameobjects as we need
	void Render();//render function for rendering the GameObject instance
private:
	int xpos;// x coordinate position
	int ypos;// y coordinate position

	SDL_Texture* objTexture;//texture for rendering
	SDL_Rect srcRect, destRect;//for drawing and placing
	
};

