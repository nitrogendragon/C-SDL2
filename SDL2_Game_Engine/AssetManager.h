#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "ECS/ECS.h"
#include "Vector2D.h"
#include "SDL_ttf.h"
class AssetManager
{
public:
	
	//constructs our asset manager taking in a pointer to a manager object
	AssetManager(Manager* man);
	~AssetManager();

	//gameobjects
	//creates our projectiles taking in Vector2D position, vector2D velocity,x and y scale, range, speed, projectiles index within the projectiles array, vIndex index within the entities vector and a isAnim bool to know if it is animated
	void CreateProjectile(Vector2D pos, Vector2D vel, int xscale, int yscale, int range, int speed, int projectilesIndex, bool isAnim = false);
	//resets the projectile



	//texture management
	void AddTexture(std::string id, const char* path);//takes in file path and an id for the texture to be added and adds it
	SDL_Texture* GetTexture(std::string id);//returns a pointer to the texture in our textures map using its id or key value
	//adds a font
	void AddFont(std::string id, std::string path, int fontSize);
	
	//returns a font
	TTF_Font* GetFont(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures;//map list of our textures, takes in a key value string and a pointer to the texture
	
	std::map<std::string, TTF_Font*> fonts;//map that holds our fonts
	
	
	Manager* manager;
	

	
};

