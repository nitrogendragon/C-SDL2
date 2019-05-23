
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace std;
Map* map1;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;//SDL_Event event variable
//creates a Manager class instance manager in our game
Manager manager;
//gives access to our list of collider components
vector<ColliderComponent*> Game::colliders;
//creates and adds a player Entity to our manager
auto& player(manager.addEntity());

//creates a wall
auto& wall(manager.addEntity());

const char* mapfile = "Assets/WorldPieces_32x32.png";
//labels for our groups
enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

Game::Game()
{

}


Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;// determines whether we do fullscreen or not.. 0 would be equated to false and 1 is true
	if (fullscreen)// if we pass a true bool or 1
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
	//make a new Map map
	map1 = new Map();




	//ecs implementation
	//loads our map TMap which is a tilemap of 32x32 pixel tiles
	Map::LoadMap("Assets/TMap_60x30.txt", 60, 30);

	//gives our player a position, height, width and height and width scaling component
	player.addComponent<TransformComponent>(100, 100, 64, 64, 3, 3);
	//gives our player a sprite component and sets it to ninjagirl_66x88.png
	player.addComponent<SpriteComponent>("Assets/slime_animated_64x64_15x15x5x5x5x5_frames.png", true);
	//let us control our player among other things
	player.addComponent<KeyBoardController>();
	//add collision detection to our player and give it the player tag
	player.addComponent<ColliderComponent>("player");
	//adds player to groupPlayers groupLabel
	player.addGroup(groupPlayers);




}

void Game::handleEvents() //function for handling game events
{
	
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
	//moving through our games entities each frame and getting rid of those that aren't there/active anymore
	manager.refresh();
	//runs the managers update function to update all the components
	manager.update();
	//checking for our player and wall collision
	for (auto cc : colliders) 
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}

}
//map objects list aka tiles list
auto&tiles(manager.getGroup(groupMap));
//players list
auto& players(manager.getGroup(groupPlayers));
//enemies list
auto& enemies(manager.getGroup(groupEnemies));


void Game::render()//function for rendering the game
{
	SDL_RenderClear(renderer);//clears the rendering target which in this case is our Game class renderer
	
	//draws our tiles for our map
	for (auto& t : tiles)
	{
		t->draw();
	}
	//draws our players
	for (auto& p : players)
	{
		p->draw();
	}
	//draws our enemies
	for (auto& e : enemies)
	{
		e->draw();
	}
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


//implementation of our addtile Game Class function
//takes in (int x, int y, int id, int h, int w) for position x and y, tile id, and height and width which have default values of 32
void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);

}

