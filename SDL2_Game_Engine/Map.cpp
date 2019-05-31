#include "Map.h"
#include "Game.h"
//parsing files
#include <fstream>
#include <iostream>
#include "ECS/ECS.h"
#include"ECS/Components.h"


extern Manager manager;
using namespace std;

Map::Map(const char* mfp, int ms, int ts) 
{
	mapFilePath = mfp;
	mapScale = ms; 
	tileSize = ts;
	scaledSize = ms * ts;
}

Map::~Map()
{

}
//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int xPix, int yPix,int xScale, int yScale ) 
//filename path, X and Y size of map, height and width dimensions of tiles
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	//taking in character by character when reading the file for getting our tiles
	char c;
	//holder for srcX or Y value depending on situation
	char holdchar;
	
	//object to store the file we are loading
	std::fstream mapFile;
	
	//open our mapfile
	mapFile.open(path);
	//parsigng file
	
	int srcX, srcY = 0;

	for (int y = 0; y < sizeY; y++)
	{
		//std::cout << y << " ";
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);//get our first char value
			//std::cout << c;
			holdchar = c;//hold it in case comma is next
			mapFile.get(c);//get second char value
			if (c != ',') //not a comma?
			{
				//std::cout << c<<", ";
				if (c == '0') 
				{
					srcY = (atoi(&holdchar)) * tileSize - tileSize;//y gets the held value
					srcX = (atoi(&c)+9) * tileSize;//x gets the new value and we minus 1 to adjust for 0 start index
					mapFile.ignore();//ignore the next value because we know its a comma
				}
				else
				{
					srcY = (atoi(&holdchar)) * tileSize;//y gets the held value
					srcX = (atoi(&c)-1) * tileSize;//x gets the new value and we minus 1 to adjust for 0 start index
					mapFile.ignore();//ignore the next value because we know its a comma
				}
			}
			else
			{
				srcY = 0;
				srcX = (atoi(&holdchar)-1) * tileSize;
			}
			
			AddTile(srcX, srcY, x * (scaledSize), y * (scaledSize));

		}
		//std::cout << endl;
	}
	
	mapFile.ignore();//ignoring the blank line between layers
	//loop for second layer aka collider layer
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * (scaledSize), y * (scaledSize),scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}
	//close our map file
	mapFile.close();
}
//implementation of our addtile Game Class function
//takes in (int x, int y,int xpos, int ypos, int tsize, int tscale) for position x and y, tile id, and height and width which have default values of 32
void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);

}


