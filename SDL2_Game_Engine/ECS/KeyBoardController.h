#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "TransformComponent.h"
class KeyBoardController : public Component
{
	bool wdown = false;
	bool adown = false;
	bool sdown = false;
	bool ddown = false;
	bool spacedown = false;
public:
	//pointer to our transform component
	TransformComponent *transform;
	SpriteComponent *sprite;
	void init() override
	{
		//sets transform to point to the address of the entity TransformComponent
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		//is the key no longer down?
		if (Game::event.type == SDL_KEYUP)
		{
			if (Game::event.key.keysym.sym == SDLK_w && wdown == true)
			{
				transform->velocity.y = 0;
				sprite->Play("Idle");
				wdown = false;
				sdown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_a && adown == true)
			{
				transform->velocity.x = 0;
				sprite->Play("Idle");
				adown = false;
				ddown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_d && ddown == true)
			{

				transform->velocity.x = 0;
				sprite->Play("Idle");
				adown = false;
				ddown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_s && sdown == true)
			{
				transform->velocity.y = 0;
				sprite->Play("Idle");
				sdown = false;
				wdown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_SPACE && spacedown == true)
			{
				sprite->Play("Idle");
				spacedown = false;
			}
		}

		//is a key down?
		if (Game::event.type == SDL_KEYDOWN)
		{
			//determining based on key down whether to give certain kinds of forces to our player for wasd inputs
			//other actions to be added
			if (Game::event.key.keysym.sym == SDLK_w && wdown == false)
			{
				transform->velocity.y = -10;
				sprite->Play("RollUp");
				wdown = true;
				
			}
			if (Game::event.key.keysym.sym == SDLK_a && adown == false)
			{
				transform->velocity.x = -10;
				sprite->Play("RollLeft");
				adown = true;
			}
			if (Game::event.key.keysym.sym == SDLK_d && ddown == false)
			{
			
				transform->velocity.x = 10;
				sprite->Play("RollRight");
				
				ddown = true;
			}
			if (Game::event.key.keysym.sym == SDLK_s && sdown == false)
			{
				transform->velocity.y = 10;
				sprite->Play("RollDown");
				sdown = true;
			}
			if (Game::event.key.keysym.sym == SDLK_SPACE && spacedown == false)
			{
				sprite->Play("Blast");
				spacedown = true;
			}
		}

		
	}


};