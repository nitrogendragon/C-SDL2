#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include <iostream>
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();//handles events quite literally
	void update();//handles updating the game
	void render();//renders Game elements
	void clean();//clear game of memory
	bool running() { return isRunning; }

	static SDL_Renderer*renderer;
private:
	int cnt = 0;//cnt for various purposes but mostly not needed
	bool isRunning = false;//is the game running?
	SDL_Window *window;//pointer to our window
	

		
};

