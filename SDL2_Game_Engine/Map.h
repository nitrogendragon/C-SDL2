#pragma once
#include "Game.h"
class Map
{
public:
	//creates map with params x and y for src location(probably both 0), src height and width(probably base dimensions of img, and scale for height and width via H/WScale(will vary but 1 would be good to start with)
	Map();
	~Map();

	void LoadMap(string path, int sizeX, int sizeY);
	
private:

};

