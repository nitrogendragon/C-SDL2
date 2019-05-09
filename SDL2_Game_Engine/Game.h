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
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();//handles events quite literally
	void update();//handles updating the game
	void render();//renders Game elements
	void clean();//clear game of memory
	bool running() { return isRunning; }
	//method to add tiles taking in the an id for the tileid, and an x and y position for placement
	static void AddTile( int x, int y, int id, int h =32, int w = 32);
	//pointer of type SDL_Renderer
	static SDL_Renderer* renderer;
	//can access event from anywhere now
	static SDL_Event event;
	//holds our colliders
	static std::vector<ColliderComponent*> colliders;


private:
	int cnt = 0;//cnt for various purposes but mostly not needed
	bool isRunning = false;//is the game running?
	SDL_Window *window;//pointer to our window
	

		
};

