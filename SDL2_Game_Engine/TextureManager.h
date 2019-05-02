#pragma once
#include "Game.h"
class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* filename);//loads file as a texture to the specified renderer
	TextureManager();
	~TextureManager();
};

