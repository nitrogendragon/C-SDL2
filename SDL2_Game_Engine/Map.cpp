#include "Map.h"
#include "Game.h"
//parsing files
#include <fstream>
#include <iostream>
using namespace std;

Map::Map()
{

}

Map::~Map()
{

}
//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int xPix, int yPix,int xScale, int yScale ) 
//filename path, X and Y size of map, height and width dimensions of tiles
void Map::LoadMap(std::string path, int sizeX, int sizeY,int xPix, int yPix, int xScale, int yScale)
{
	//taking in character by character when reading the file for getting our tiles
	char c;
	//holder for srcX or Y value depending on situation
	char holdchar;
	int xPixDim = xPix;
	int yPixDim = yPix;
	int XScale = xScale;
	int YScale = yScale;
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
					srcY = (atoi(&holdchar)) * yPixDim - yPixDim;//y gets the held value
					srcX = (atoi(&c)+9) * xPixDim;//x gets the new value and we minus 1 to adjust for 0 start index
					mapFile.ignore();//ignore the next value because we know its a comma
				}
				else
				{
					srcY = (atoi(&holdchar)) * yPixDim;//y gets the held value
					srcX = (atoi(&c)-1) * xPixDim;//x gets the new value and we minus 1 to adjust for 0 start index
					mapFile.ignore();//ignore the next value because we know its a comma
				}
			}
			else
			{
				srcY = 0;
				srcX = (atoi(&holdchar)-1) * xPixDim;
			}
			//the *2 should scale it
			Game::AddTile(srcX, srcY, x * xPixDim, y * yPixDim);

		}
		//std::cout << endl;
	}
	std::cout << "still working" << endl;
	//close our map file
	mapFile.close();
}



