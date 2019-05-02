#pragma once
#include "Game.h"
class Map
{
public:
	//creates map with params x and y for src location(probably both 0), src height and width(probably base dimensions of img, and scale for height and width via H/WScale(will vary but 1 would be good to start with)
	Map(int x, int y, int srcRectH, int srcRectW, float hScale, float wScale);
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	
private:
	SDL_Rect src, dest;//src and dest SDL_Rects for seeting up how much of the texture we want to use and what scale to give it
	SDL_Texture* dirt;//dirt texture
	SDL_Texture* grass;//grass texture
	SDL_Texture* water;//water texture
	
	int map[20][25];
};

