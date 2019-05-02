
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;//player GameObject
GameObject* enemy;//enemy GameObject
Map* map;
SDL_Renderer* Game::renderer = nullptr;


Game::Game()
{

}


Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
{
	int flags = 0;// determines whether we do fullscreen or not.. 0 would be equated to false and 1 is true
	if(fullscreen)// if we pass a true bool or 1
	{
		flags = SDL_WINDOW_FULLSCREEN;// flags is 1 or true so we are fullscreen
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // if we haven't initialized all of the SDL subsystems then do so
	{
		cout << "Subsystems Initialized!..." << endl;//just letting us know that we have initialized everything

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);//create our window with a title position and dimensions assuming flags is 1 which it should be
		if (window)// if true or 1 which it should be
		{
			cout << "Window created" << endl;// let us know we created the window
		}

		renderer = SDL_CreateRenderer(window, -1, 0);//creates 2D rendering context for rendering window
		if (renderer)// if we have the renderer which we should
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);// set the color of the window
			cout << "Renderer created!" << endl;// let us know we created the renderer window
		}

		isRunning = true;//we are running
	}
	
	player = new GameObject("Assets/ninjagirl.png",10,10,93,93,1.0,1.0);//creates/renders player GameObject
	enemy = new GameObject("Assets/firsttry.png",50,10,300,200,.5,.5);//creates/renders player GameObject
	map = new Map(0,0,32,32,1.0,1.0);//makes a new map
}

void Game::handleEvents() //function for handling game events
{
	SDL_Event event;//SDL_Event event variable
	SDL_PollEvent(&event);//polls our event to see if there are events to be handled
	switch (event.type) //depending on the event
	{
		case SDL_QUIT://if we have asked to quit
			isRunning = false;//we are no longer running
				break;//break out of the switch statement

		default://by default if none of the previous cases stood
			break;//break out of the switch statement
	}
}
void Game::update()//function for updating the game
{
	player->Update();//runs players update function
	enemy->Update();//runs enemy update function
}
void Game::render()//function for rendering the game
{
	SDL_RenderClear(renderer);//clears the rendering target which in this case is our Game class renderer
	map->DrawMap();//draws our map for us
	//this is where we add stuff to render
	//order determines layer.. first in the back last in the front
	player->Render();//renders our player
	enemy->Render();//renders our enemy
	SDL_RenderPresent(renderer);//updates the screen with the new renderer renderings
}
void Game::clean()//clear game of memory
{
	SDL_DestroyWindow(window);//as it says destroys our game window
	SDL_DestroyRenderer(renderer);//destroys our game renderer
	SDL_Quit();//cleans up all the initialized subsystems ..call whenever we are exiting/on exit conditions
	cout << "Game Cleaned" << endl;//let us know the game is cleaned up
}

