#pragma once
#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#pragma once
#include<SDL.h>

#include <string>
//colors

//handles the actual health stat of the entity as well as rendering health bars
//rendering takes in int x, int y, int h, int w, float percent, SDL_Color FGColor, SDL_Color BGColor
class Health : public Component
{
private:
	
	TransformComponent *transform;
	//texture for the sprite 
	//texture for the sprite 
	SDL_Texture *bgTexture, *fgTexture, *borderTexture;
	//our SDL_Rects for our three Sprites that make up the healthbar
	SDL_Rect bgRect, fgRect, borderRect;
	float Percent = .7f;

public:
	//constructor
	Health() {};
	~Health() {};
	//renders our hit points based on what percent of our health remains
	void RenderHPBar(int x, int y, int h, int w, float percent)
	{
		//updating percent health left
		Percent = percent > 1.f ? 1.f : Percent < 0.f ? 0.f : percent;
		//set bgrect
		bgRect = { x, y, w, h };
		//set border rect
		borderRect = { x,y,w,h };
		//set  width of fgRect based on percent
		int pw = (int)((float)w * Percent);
		//adjust how much of the bar is drawn
		int px = x + (w - pw);
		//set up fgRect
		fgRect = { px, y, pw, h };
		//set textures for our healthbar
		setTex("HealthBarFG_150x25.png", "BGroundHealthBar150x25.png", "BorderHealthBar_150x25.png");
	
	}
	//sets up our players health bar 
	void RenderPlayerHealth()
	{
		cout << this << endl;
		RenderHPBar(0, 0, 30, 150, Percent);
		//set textures for our healthbar
		
	}
	//set texture function taking in string fgid, bgid and borderid to grab healthbar textures
	void setTex(std::string fgid, std::string bgid, std::string borderid)
	{
		fgTexture = Game::assets->GetTexture(fgid);
		bgTexture = Game::assets->GetTexture(bgid);
		borderTexture = Game::assets->GetTexture(borderid);
	
	}
	
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	
	}
	
	
	void draw() override
	{
		TextureManager::Draw(bgTexture, bgRect, bgRect, SDL_FLIP_NONE);
		TextureManager::Draw(fgTexture, fgRect, fgRect, SDL_FLIP_NONE);
		TextureManager::Draw(borderTexture, borderRect, borderRect, SDL_FLIP_NONE);
	}
	
};