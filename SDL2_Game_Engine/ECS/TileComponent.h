#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include "../AssetManager.h"
//creates a TileComponent
//constructor form is as follows (TileComponent(int x, int y, int id, int h, int w)
//x and y starting rendering points, w and h size parameters, id for identifying specific tiles
class TileComponent : public Component
{
public:
	int pVelX;
	int pVelY;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	Vector2D position;//position of our tiles
	TileComponent() = default;
	
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	//set up tile position and dimensions... takes in int srcX, int srcY, int xpos, int ypos,int tsize, int tscale, std::string id
	TileComponent(int srcX, int srcY, int xpos, int ypos,int tsize, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);
		position.x = xpos;
		position.y = ypos;
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}
	//takes in an entity "the player" and gets their velocity to know how fast to move the tiles.
	void ScrollTiles(Entity&player, std::vector<Entity*> tiles)
	{
		pVelX = player.getComponent<TransformComponent>().xvel;
		pVelY = player.getComponent<TransformComponent>().yvel;

		for (auto t : tiles)
		{
			t->getComponent<TileComponent>().destRect.x += -(pVelX);
			t->getComponent<TileComponent>().destRect.y += -(pVelY);
		}
	}
	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};