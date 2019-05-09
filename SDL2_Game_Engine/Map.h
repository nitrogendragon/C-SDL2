#pragma once
#include "Game.h"
#include <string>
class Map
{
public:
	//creates map with params x and y for src location(probably both 0), src height and width(probably base dimensions of img, and scale for height and width via H/WScale(will vary but 1 would be good to start with)
	Map();
	~Map();
	//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int h, int w) 
	//filename path, X and Y size of map, height and width dimensions of tiles
	static void LoadMap(std::string path, int sizeX, int sizeY, int h =32, int w = 32);
	
private:

};

