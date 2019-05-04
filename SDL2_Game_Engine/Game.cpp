
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"


Map* map;
SDL_Renderer* Game::renderer = nullptr;
//creates a Manager class instance manager in our game
Manager manager;
//creates and adds a player Entity to our manager
auto& player(manager.addEntity());

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
	
	map = new Map(0,0,32,32,1.0,1.0);//makes a new map
	//gives our player a position component
	player.addComponent<PositionComponent>(100,100);
	//gives our player a sprite component and sets it to rogueone
	player.addComponent<SpriteComponent>("Assets/ninjagirl_66x88.png",0,0,66,88,.5,.5);
	
	
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
//temporary counter for showing dmg dealt example via texswapping
//int cnt = 0;
void Game::update()//function for updating the game
{
	//example for animating dmg so to speak via color changing
	/*if (player.getComponent<PositionComponent>().x() > 100 && cnt < 1)
	{
		player.getComponent<SpriteComponent>().setTex("Assets/ninjagirl_damaged_66x88.png");
	}
	else 
	{ 
		player.getComponent<SpriteComponent>().setTex("Assets/ninjagirl_66x88.png"); 
	}
	if (cnt < 2) 
	{
		cnt++;
	}
	else
	{
		cnt = 0;
	}*/
			
		
	
	//moving through our games entities each frame and getting rid of those that aren't there/active anymore
	manager.refresh();
	//runs the managers update function to update all the components
	manager.update();
	
}
void Game::render()//function for rendering the game
{
	SDL_RenderClear(renderer);//clears the rendering target which in this case is our Game class renderer
	map->DrawMap();//draws our map for us
	manager.draw();//runs the manager draw fucntion to draw  entities
	//this is where we add stuff to render
	//order determines layer.. first in the back last in the front

	SDL_RenderPresent(renderer);//updates the screen with the new renderer renderings
}
void Game::clean()//clear game of memory
{
	SDL_DestroyWindow(window);//as it says destroys our game window
	SDL_DestroyRenderer(renderer);//destroys our game renderer
	SDL_Quit();//cleans up all the initialized subsystems ..call whenever we are exiting/on exit conditions
	cout << "Game Cleaned" << endl;//let us know the game is cleaned up
}

