#include "TextureManager.h"
//manager for loading and creating(rendering) textures in the game, takes in file name texture and renderer ren
SDL_Texture* TextureManager::LoadTexture(const char* texture) 
{
	SDL_Surface* tempSurface = IMG_Load(texture);//temporary surface for the texture file loaded
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);//creates texture from surface and well renders it
	SDL_FreeSurface(tempSurface);//gets rid of or frees the tempSurface surface we made to create the texture

	return tex;//returns our new texture tex
}


TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{

}
