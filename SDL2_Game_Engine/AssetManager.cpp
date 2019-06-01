#include "AssetManager.h"



AssetManager::AssetManager(Manager* man) : manager (man)
{
	
}

//takes in file path and an id for the texture to be added and adds it
void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));//puts our texture into our textures map
}

//returns a pointer to the texture in our textures map using its id or key value
SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}


AssetManager::~AssetManager()
{
}
