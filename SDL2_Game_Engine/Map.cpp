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
//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int h, int w) 
//filename path, X and Y size of map, height and width dimensions of tiles
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	//taking in character by character when reading the file for getting our tiles
	char tile;
	std::string str;
	
	//object to store the file we are loading
	std::fstream mapFile;
	
	//open our mapfile
	mapFile.open(path);
	//parsigng file

/*	for (int y = 0; y < sizeY+6; y++) 
	{
		
		for (int x = 0; x < sizeX; x++)
		{
			if (y < 6) {
				getline(mapFile, str);

			}
			else {



				mapFile.get(tile);
				cout << tile << endl;
				//create tile in position (x * width, y * height), convert character tile to int for setting up tileid,
				//and set the height and width as desired...Note that h and w have default values of 32
				Game::AddTile(atoi(&tile), x * 32, (y-6) * 32);
				mapFile.ignore(); 
			}
		}
		//mapFile.ignore();
	}
		
*/		
	
				
	for (int y = 0; y < sizeY; y++)
	{
		getline(mapFile, str);
		cout << str << endl;
		for (int x = 0; x < sizeX; x++)
		{
			
			



			//tile = str[(x * 2)];
			cout << str[x*2]<< endl;
			//create tile in position (x * width, y * height), convert character tile to int for setting up tileid,
			//and set the height and width as desired...Note that h and w have default values of 32
			Game::AddTile(atoi(&str[x*2]), x * 32, y * 32);
				
			
		}
		//mapFile.ignore();
	}
					
					
		
			

		

	cout << "still working" << endl;
	//close our map file
	mapFile.close();
}



