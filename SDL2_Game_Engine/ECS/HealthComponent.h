#pragma once
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"
#include "../Game.h"


#include<SDL.h>
#include "../Vector2D.h"
#include <math.h>
#include <string>
//colors


//handles the actual health stat of the entity as well as rendering health bars
//rendering takes in int x, int y, int h, int w, float percent, Entity* character
class HealthComponent : public Component
{
private:
	
	
	//holds position of character entity
	int posx, posy;
	
	float curPercent = 1.0f;
	bool animated = false;
	bool isplayer = false;
	int enemyid = 0;
	
public:
	
	float newPercent = 1.0f;
	//constructor
	HealthComponent() {};
	HealthComponent(bool player, int enemid)
	{
		isplayer = player;
		enemyid = enemid;
		
		
		
	
	};
	~HealthComponent() {};
	//renders our hit points based on what percent of our health remains 
	// takes in int x, int y, int h, int w,float percent, Entity* character, Entity* healthbar
	/*void UpdateHBBackground(Entity* character, Entity* healthbar)
	{
		healthbar->getComponent<HealthComponent>().curPercent = newPercent;
		healthbar->getComponent<TransformComponent>().position.x =
			character->getComponent<TransformComponent>().position.x - 400;
		healthbar->getComponent<TransformComponent>().position.y =
			character->getComponent<TransformComponent>().position.y - 400;
	}*/
	void UpdateHPBar( int x, int y, int h, int w, float percent, Entity* character)
	{
		//updating percent health left
		curPercent = percent > 1.f ? 1.f : curPercent < 0.f ? 0.f : percent;

		//set  width of fgRect based on percent
		int pw = (int)((float)w * curPercent);
		//adjust how much of the bar is drawn
		int px = x + (w - pw);
		//adjusts healthbar display based on damage taken and also scales it
		//Adjusts SpriteComponent transforms to alter the life being displayed
		entity->getComponent<SpriteComponent>().transform->position.x = px;
		entity->getComponent<SpriteComponent>().transform->width = pw;
		//Adjusts the actual in game screen position of the healthbar
		entity->getComponent<TransformComponent>().position = Vector2D(
			character->getComponent<TransformComponent>().position.x - 400,
			character->getComponent<TransformComponent>().position.y - 400);
	}

	//sets up our players health bar 
	void UpdatePlayerHealth()
	{
		
		
		//set textures for our healthbar
		
	}

	
	
};