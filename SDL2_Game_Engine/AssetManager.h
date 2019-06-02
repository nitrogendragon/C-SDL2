#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS/ECS.h"
#include "Vector2D.h"

class AssetManager
{
public:
	
	//constructs our asset manager taking in a pointer to a manager object
	AssetManager(Manager* man);
	~AssetManager();

	//gameobjects
	//creates our projectiles taking in Vector2D position, vector2D velocity, range, speed, projectiles index within the projectiles array, and a isAnim bool to know if it is animated
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, int projectilesIndex, bool isAnim);
	


	//texture management
	void AddTexture(std::string id, const char* path);//takes in file path and an id for the texture to be added and adds it
	SDL_Texture* GetTexture(std::string id);//returns a pointer to the texture in our textures map using its id or key value
private:
	std::map<std::string, SDL_Texture*> textures;//map list of our textures, takes in a key value string and a pointer to the texture
	Manager* manager;
	;
	
};

