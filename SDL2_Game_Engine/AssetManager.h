#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS/ECS.h"

class AssetManager
{
public:
	//constructs our asset manager taking in a pointer to a manager object
	AssetManager(Manager* man);
	~AssetManager();

	void AddTexture(std::string id, const char* path);//takes in file path and an id for the texture to be added and adds it
	SDL_Texture* GetTexture(std::string id);//returns a pointer to the texture in our textures map using its id or key value
private:
	std::map<std::string, SDL_Texture*> textures;//map list of our textures, takes in a key value string and a pointer to the texture
	Manager* manager;
};

