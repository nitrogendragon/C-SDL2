#include "Map.h"
#include "Game.h"
//parsing files
#include <fstream>

int rows = 20;//rows placeholder for now
int cols = 25;//cols placeholder for now
//ugly mapping of 2D array lvl1 20x25

Map::Map()
{

}

Map::~Map()
{

}
//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int h, int w) 
//filename path, X and Y size of map, height and width dimensions of tiles
void Map::LoadMap(std::string path, int sizeX, int sizeY, int h, int w)
{
	//taking in character by character when reading the file for getting our tiles
	char tile;
	//object to store the file we are loading
	fstream mapFile;
	//open our mapfile
	mapFile.open(path);
	//parsigng file
	for (int y = 0; y < sizeY;y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			//puts our character in tile
			mapFile.get(tile);
			//create tile in position (x * width, y * height), convert character tile to int for setting up tileid,
			//and set the height and width as desired...Note that h and w have default values of 32
			Game::AddTile(x *w, y * h, atoi(&tile));
			//ignore commas
			mapFile.ignore(2);
		}
	}
	//close our map file
	mapFile.close();
}



