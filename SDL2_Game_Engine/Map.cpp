#include "Map.h"
#include "TextureManager.h"
int rows = 20;//rows placeholder for now
int cols = 25;//cols placeholder for now
//ugly mapping of 2D array lvl1 20x25
int lvl1[20][25] =
{
	{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//creates map with params x and y for src location(probably both 0), src height and width(probably base dimensions of img, and scale for height and width via H/WScale(will vary but 1 would be good to start with)
Map::Map(int x, int y, int srcRectH, int srcRectW, float hScale, float wScale)//creates map with params x and y for src location(probably both 0), src height and width(probably base dimensions of img, and scale for height and width via H/WScale(will vary but 1 would be good to start with)
{
	
	dirt = TextureManager::LoadTexture("Assets/simpleground_32x32.png");//loads dirt texture
	grass = TextureManager::LoadTexture("Assets/simplegrass_32x32.png");//loads grass texture
	water = TextureManager::LoadTexture("Assets/simplewater_32x32.png");//loads water texture
	LoadMap(lvl1);//loads our lvl1 map 2D array
	src.x = 0;//starting x point basically beginning of img
	src.y = 0;//starting y point basically beginning of img
	src.h = srcRectH;//sets how many of the heightwise pixels we will be rendering
	src.w = srcRectW;//sets how many of the widthwise pixels we wlll be rendering
	dest.h = src.h *hScale;//scales texture height
	dest.w = src.w *wScale;//scales texture width
	dest.x = x;//sets x pos on window to whatever we pass th x parameter as
	dest.y = y;//sets y pos on window to whatever we pass the y parameter as

}


Map::~Map()
{
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0;row < 20;row++)
	{
		for (int column = 0;column < 25;column++)
		{
			map[row][column] = arr[row][column];//sets up map based on pre-made 2D arrays
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0;row < 20;row++)
	{
		for (int column = 0;column < 25;column++)
		{
			type = map[row][column];//sets type equal to the int value of the map at the current array indices
			dest.x = column * src.w;//move across the screen by width of texture every increment of column
			dest.y = row * src.h;//move down the screen by height of texture every increment of row
			switch (type)//switch statement using our integer type as the case basis variable
			{
			case 0://if type ==0
				TextureManager::Draw(water, src, dest);
				break;
			case 1://if type ==1
				TextureManager::Draw(grass, src, dest);
				break;
			case 2://if type ==2
				TextureManager::Draw(dirt, src, dest);
				break;
			default:
				break;
			}
		}
	}
}
