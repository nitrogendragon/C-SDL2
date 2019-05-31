#pragma once
#include <string>
class Map
{
public:
	Map(const char* mfp, int ms, int ts);
	~Map();
	//loads our map from the file we choose. takes in (string path, int sizeX, int sizeY) 
	//filename path, X and Y # of tiles to the map
	void LoadMap(std::string path, int sizeX, int sizeY);
	//another method to add tiles taking in srcX and Y dimensions and x and y positions
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	
private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};

