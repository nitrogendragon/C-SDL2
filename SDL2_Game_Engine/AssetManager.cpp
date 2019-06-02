#include "AssetManager.h"
#include "ECS/Components.h"
#include "ECS/ProjectileComponent.h"

AssetManager::AssetManager(Manager* man)
{
	manager = man;
}
AssetManager::~AssetManager()
{

}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int xscale, int yscale, int range, int speed, int projectilesIndex, bool isAnim = false)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, xscale, yscale);
	projectile.addComponent<SpriteComponent>(projectiles[projectilesIndex], isAnim);
	projectile.addComponent<ProjectileComponent>(pos,xscale, yscale, range, speed, vel.x, vel.y,projectilesIndex, isAnim);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
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



