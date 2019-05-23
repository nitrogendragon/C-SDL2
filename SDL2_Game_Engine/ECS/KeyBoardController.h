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
	bool isIdle = false;
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
		/** //is a key down?
		if (Game::event.type == SDL_KEYDOWN)
		{
			//determining based on key down whether to give certain kinds of forces to our player for wasd inputs
			//other actions to be added
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -10;
				sprite->Play("RollUp");
				wdown = true;
				break;
			case SDLK_a:
				transform->velocity.x = -10;
				sprite->Play("RollLeft");
				break;
			case SDLK_d:
				transform->velocity.x = 10;
				sprite->Play("RollRight");
				break;
			case SDLK_s:
				transform->velocity.y = 10;
				sprite->Play("RollDown");
				break;
			case SDLK_SPACE:
				sprite->Play("Blast");
				break;
			default:
				break;
			}
		}

		//is the key no longer down?
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//for now we are setting to zero automatically but this will probably need changed when gravity is properly iplemented with collison detection
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				//for now we are setting to zero automatically but this will probably need changed when gravity is properly iplemented with collison detection
				transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_SPACE:
				sprite->Play("Idle");
				break;
			default:
				break;
			}
		}
		/**/

		//is the key no longer down?
		//
		if (Game::event.type == SDL_KEYUP)
		{
			if (Game::event.key.keysym.sym == SDLK_w && wdown == true)
			{
				transform->velocity.y = 0;
				
				wdown = false;
				sdown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_a && adown == true)
			{
				transform->velocity.x = 0;
				
				adown = false;
				ddown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_d && ddown == true)
			{

				transform->velocity.x = 0;
				
				adown = false;
				ddown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_s && sdown == true)
			{
				transform->velocity.y = 0;
				
				sdown = false;
				wdown = false;
			}
			if (Game::event.key.keysym.sym == SDLK_SPACE && spacedown == true)
			{
				
				spacedown = false;
				sprite->Play("Idle");
			}
			//we dont want to go into idle unless we aren't moving
			if (!wdown && !sdown && !ddown && !adown && !isIdle)
			{
				sprite->Play("Idle");
				isIdle = true;
				
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
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				transform->velocity.x = -10;
				sprite->Play("RollLeft");
				adown = true;
			}
			if (Game::event.key.keysym.sym == SDLK_d && ddown == false)
			{
				//sprite->spriteFlip = SDL_FLIP_NONE;
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
				transform->velocity.x = 0;
				transform->velocity.y = 0;
				sprite->Play("Blast");
				spacedown = true;
			}
			isIdle = false;
		}
		//
	}


};