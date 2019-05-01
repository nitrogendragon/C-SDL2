#pragma once
#include "Game.h"
class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);//loads file as a texture to the specified renderer
	TextureManager();
	~TextureManager();
};

