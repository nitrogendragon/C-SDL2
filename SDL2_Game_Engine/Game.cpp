
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ECS/TransformComponent.h"
#include "AssetManager.h"
#include "ECS/ProjectileComponent.h"
#include <sstream>
using namespace std;
Map* map1;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;//SDL_Event event variable
//creates a Manager class instance manager in our game
Manager manager;



//creates a tilecomponent instance
//TileComponent tileManager;

SDL_Rect Game::camera{ 0,0,1920,1024};//our camera and its position and field of view

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect playerCol;//variable for holding our players collider
Vector2D playerPos = NULL;//variable for holding our players collider
bool Game::isRunning = false;
//creates and adds a player Entity to our manager
Entity& player(manager.addEntity());

//creates a label Entity reference and adds it to our manager 
Entity& label(manager.addEntity());
//forward declaration of our projectile components
ProjectileComponent pComponents;
//holds players xvel as an int..
int pVelX = NULL;
//holds players y velocity as an int..
int pVelY = NULL;

//labels for our groups



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
		winWidth = width;
		winHeight = height;
		camera = { 0,0,winWidth,winHeight };
		cout << winWidth << " " << winHeight << endl;
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


	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	//Adding our textures to our assets manager

	assets->AddTexture("terrain", "Assets/WorldPieces_32x32.png");
	assets->AddTexture("player", "Assets/slime_animated_64x64_15x15x5x5x5x5_frames.png");
	assets->AddTexture("slime_ki_blast", "Assets/slime_ki_blast_32x32_7.png");
	assets->AddTexture("boxcol", "assets/boxcoltex_32x32.png");
	assets->AddTexture("PlayerFGHB", "HealthBarFG_150x25.png");
	assets->AddTexture("PlayerBGHB","BGroundHealthBar150x25.png" );
	assets->AddTexture("PlayerBorderHB", "BorderHealthBar_150x25.png");
	

	//adding a font to our fonts
	assets->AddFont("timesbd", "assets/timesbd.ttf", 16);
	//make a new Map map
	map1 = new Map("terrain", 3, 32);

	//ecs implementation
	//loads our map TMap which is a tilemap of 32x32 pixel tiles
	map1->LoadMap("Assets/TMap_60x30.txt", 60, 30);
	
	/*gives our player a position in the center of the screen, height, width and height and width scaling component
	*note that we need to adjust position by half of the size of the entity * scale to center 
	*also note that for whatever reason the window is backwards so winHeight seems to deal with width and visa versa for winWidth
	*/
	player.addComponent<TransformComponent>(64, 64, 3, 3);
	//cout << player.getComponent<TransformComponent>().position.x << " " << player.getComponent<TransformComponent>().position.y << endl;
	//gives our player a sprite component and sets it to ninjagirl_66x88.png
	player.addComponent<SpriteComponent>("player", true);
	//let us control our player among other things
	player.addComponent<KeyBoardController>();
	//add collision detection to our player and give it the player tag
	player.addComponent<ColliderComponent>("player");
	//adds health to our player
	
	player.addComponent<Health>();
	
	//adds player to groupPlayers groupLabel
	player.addGroup(groupPlayers);
	//creates the color white
	SDL_Color white = { 100, 100, 100, 255 };
	label.addComponent<UILabel>(100, 100, "Test String", "timesbd", white);

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(0, 0), 3, 3, 1900, 2, 0, false);
	assets->CreateProjectile(Vector2D(700, 600), Vector2D(2, 0),3,3, 1100, 2, 0, true);
	assets->CreateProjectile(Vector2D(500, 600), Vector2D(-2, 0),2,2, 1300, 2, 0, true);
	assets->CreateProjectile(Vector2D(900, 600), Vector2D(-1, 1),4,4, 1500, 2, 0, true);
	assets->CreateProjectile(Vector2D(400, 600), Vector2D(1, -1),5,5, 1700, 2, 0, true);
	
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
std::vector<Entity*> &theProjectiles(manager.getGroup(Game::groupProjectiles));
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
	playerCol = player.getComponent<ColliderComponent>().collider;//variable for holding our players collider
	playerPos = player.getComponent<TransformComponent>().position;//variable for holding our player position
	//need to update... clean memory so that ram isn't getting continuously eaten..probably in uilabelcomponent.h file
	//
	//
	//
	//
	//
	/*
	std::stringstream ss;
	ss << "Player position " << playerPos;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "timesbd");
	*/
	//
	//
	//
	//
	//
	player.getComponent<Health>().RenderPlayerHealth();
	
	//moving through our games entities each frame and getting rid of those that aren't there/active anymore
	manager.refresh();
	//runs the managers update function to update all the components
	manager.update();
	
	for (Entity*c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))//if player hits a collider
		{
			//player.getComponent<TransformComponent>().xvel = 0;//stop movement in x direction
			//player.getComponent<TransformComponent>().yvel = 0;//stop movement in y direction
			player.getComponent<TransformComponent>().position = playerPos;//reset position to where it was
		}
	}
	for (Entity *p : theProjectiles)
	{
		
		
		
		if (Collision::AABB(playerCol, p->getComponent<ColliderComponent>().collider))//if player hits a collider
		{
			pComponents.resetProjectile(p);
			p->destroy();
			
		}
	}
	//tileManager.ScrollTiles(player,tiles);

	camera.x = player.getComponent<TransformComponent>().position.x - winWidth / 2
		+(player.getComponent<TransformComponent>().wScale * player.getComponent<TransformComponent>().width / 2);
	camera.y = player.getComponent<TransformComponent>().position.y - winHeight / 2
		+ (player.getComponent<TransformComponent>().hScale * player.getComponent<TransformComponent>().height / 2);
	/*
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
	*/



}



void Game::render()//function for rendering the game
{
	SDL_RenderClear(renderer);//clears the rendering target which in this case is our Game class renderer
	
	//draws our tiles for our map
	for (Entity* t : tiles)
	{
		t->draw();
	}
	for (Entity* c : colliders)
	{
		c->draw();
	}
	//draws our players
	for (Entity* p : players)
	{
		p->draw();
	}
	for (Entity* p : theProjectiles)
	{
		p->draw();
	}

	label.draw();

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




