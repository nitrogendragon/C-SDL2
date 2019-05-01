#include "GameObject.h"
#include"TextureManager.h"

// creates and renders our gameobject based off the texturesheet, positions, and given dimensions / scaling based off of source dimensions
GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int srcRectH, int srcRectW, float hScale, float wScale)
{
	renderer = ren; //Sets our GameObjects SDL_Renderer renderer to whatever ren is
	objTexture = TextureManager::LoadTexture(texturesheet, ren);//loads and renders our GameObjects texture
	xpos = x;
	ypos = y;
	srcRect.h = srcRectH;//source dimension height for GameObject texture
	srcRect.w = srcRectW;//source dimension width for GameObject texture
	destRect.w = srcRect.w * wScale;// window width dimension for GameObject texture
	destRect.h = srcRect.h * hScale;// window height dimension for GameObject texture
}
GameObject::~GameObject()
{

}

void GameObject::Update() 
{
	
	xpos++;//updates x position every frame
	ypos++;//updates y position every frame

	
	srcRect.x = 0;//source x pos for GameObject texture
	srcRect.y = 0;//source y pos for GameObject texture

	destRect.x = xpos;//window x position for GameObject texture
	destRect.y = ypos;//window y position for GameObject texture
	
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);//copies specified portion of the GameObject texture to the rendering target which is our GameObject renderer
}
