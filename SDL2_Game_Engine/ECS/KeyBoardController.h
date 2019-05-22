#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "TransformComponent.h"
class KeyBoardController : public Component
{

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
		//is a key down?
		if (Game::event.type == SDL_KEYDOWN)
		{
			//determining based on key down whether to give certain kinds of forces to our player for wasd inputs
			//other actions to be added
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -10;
				sprite->Play("RollUp");
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
				//for now we are setting to zero automatically but this will probably need cahnged when gravity is properly iplemented with collison detection
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
				//for now we are setting to zero automatically but this will probably need cahnged when gravity is properly iplemented with collison detection
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
	}


};