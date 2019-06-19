#include "AssetManager.h"
#include "ECS/Components.h"
#include "ECS/ProjectileComponent.h"
#include "ECS/HealthComponent.h"
AssetManager::AssetManager(Manager* man)
{
	manager = man;
}
AssetManager::~AssetManager()
{

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int xscale, int yscale, int range, int speed, int projectilesIndex, bool isAnim)
{
	
	Entity& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, xscale, yscale);
	projectile.addComponent<SpriteComponent>(projectiles[projectilesIndex], isAnim);
	projectile.addComponent<ProjectileComponent>(pos,xscale, yscale, range, speed, vel.x, vel.y,projectilesIndex, isAnim);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
	
	
}
void AssetManager::CreateHealthBar(Vector2D pos, int w, int h, int scale, float percent, std::string fgid, bool player,int enemyid)
{
	//creates an entity for dealing with the foreground of the healthbar
	
	Entity& healthbarfg(manager->addEntity());
	healthbarfg.addComponent<TransformComponent>(pos.x, pos.y, h, w);
	healthbarfg.addComponent<SpriteComponent>(fgid, true);
	healthbarfg.addComponent<HealthComponent>(player, enemyid);
	healthbarfg.addGroup(Game::HealthBars);



}

void AssetManager::CreateHealthBarBorder(Vector2D pos, int w, int h, int scale, float percent, std::string borderid)
{


	//creates an entity for dealing with the background of the healthbar
	Entity& healthbarborder(manager->addEntity());
	healthbarborder.addComponent<TransformComponent>(pos.x, pos.y, h, w);
	healthbarborder.addComponent<SpriteComponent>(borderid);
	healthbarborder.addComponent<HealthComponent>();
	healthbarborder.addGroup(Game::HealthBarBorder);
}

void AssetManager::CreateHealthBarBG(Vector2D pos, int w, int h, int scale, float percent, std::string bgid)
{
	//creates an entity for dealing with the background of the healthbar
	Entity& healthbarbg(manager->addEntity());
	healthbarbg.addComponent<TransformComponent>(pos.x, pos.y, h, w);
	healthbarbg.addComponent<SpriteComponent>(bgid);
	healthbarbg.addComponent<HealthComponent>();
	healthbarbg.addGroup(Game::HealthBarBackGround);
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

//Adds font
void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

//returns a font
TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}



