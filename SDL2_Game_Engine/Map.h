#pragma once
#include <string>
class Map
{
public:
	Map();
	~Map();
	//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY, int xPix, int yPix) 
	//filename path, X and Y size of map, height and width dimensions of tiles
	static void LoadMap(std::string path, int sizeX, int sizeY, int xPix = 32, int y = 32);
	
private:

};

