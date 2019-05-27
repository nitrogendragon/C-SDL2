#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"


#include <iostream>
#include <vector> 
//declaration of ColliderComponent
class ColliderComponent;
using namespace std;
class Game
{
public:
	int winWidth = 1920;
	int winHeight = 1024;
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();//handles events quite literally
	void update();//handles updating the game
	void render();//renders Game elements
	void clean();//clear game of memory
	bool running() { return isRunning; }

	//another method to add tiles taking in srcX and Y dimensions and x and y positions
	static void AddTile(int srcX, int srcY, int xpos, int ypos);
	//pointer of type SDL_Renderer
	static SDL_Renderer* renderer;
	//can access event from anywhere now
	static SDL_Event event;
	//holds our colliders
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;//is the game running?
	static SDL_Rect camera;//camera object for the game

private:
	int cnt = 0;//cnt for various purposes but mostly not needed
	
	SDL_Window *window;//pointer to our window

		
};

