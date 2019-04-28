#pragma once
#include "SDL.h"
#include <iostream>
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();//clear game of memory

	bool running() { return isRunning; }
private:
	int cnt = 0;
	bool isRunning;//is the game running?
	SDL_Window *window;
	SDL_Renderer *renderer;

		
};

