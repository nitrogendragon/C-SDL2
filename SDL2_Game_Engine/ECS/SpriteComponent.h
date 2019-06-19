#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include<map>
#include "../AssetManager.h"
#include "ProjectileComponent.h"
class SpriteComponent: public Component
{
private:
	//reference to the position of the sprite
	TransformComponent *transform;
	//texture for the sprite 
	SDL_Texture *texture;
	//rects for sizing and scaling sprite
	
	//are we animated?
	bool animated = false;
	//# of frames
	int frames = 0;
	//delay between frames in miliseconds
	int speed = 200;
	//the current frame we are on
	int curFrame = 0;
	
public:
	std::string spriteid="";
	//rect for our 
	SDL_Rect srcRect, destRect;
	int animIndex = 0;
	//hold animations, taking in animation name, and an Animation object called animations
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	
	//create sprite component based path to texture img, starting img render points, number of horizontalxvertical pixels of source to render, and scaling
	SpriteComponent(std::string id)
	{
		spriteid = id;
		//creates texture by loading our image using setTex function defined after our function here
		setTex(id);
	
	}

	//create sprite component using textures tag id passed as a string, and whether its animated or not 
	SpriteComponent(string id, bool isAnimated)
	{
		spriteid = id;
		animated = isAnimated;
		Animation playerlife = Animation(0, 10, 200);
		Animation idle = Animation(0, 15, 50);
		Animation blast = Animation(1, 15, 100);
		Animation rollRight = Animation(2, 5, 50);
		Animation rollLeft = Animation(3, 5, 50);
		Animation rollDown = Animation(4, 5, 50);
		Animation rollUp = Animation(5, 5, 50);
		Animation slimeKiBlast = Animation(0, 7, 50);
		
		animations.emplace("Idle", idle);
		animations.emplace("Blast", blast);
		animations.emplace("RollRight", rollRight);
		animations.emplace("RollLeft", rollLeft);
		animations.emplace("RollUp", rollUp);
		animations.emplace("RollDown", rollDown);
		animations.emplace("SlimeKiBlast", slimeKiBlast);
		animations.emplace("PlayerLife", playerlife);
		setTex(id);
		if (id == "player")
		{
			Play("Idle");
		}
		else if (id == "PlayerFGHB")
		{
			Play("PlayerLife");
			cout << "we are playing playerlife" << endl;
		}
		else if (id == projectiles[0] || "slime_ki_blast")//slime_ki_blast
		{
			Play("SlimeKiBlast");
		}
	}

	//deconstructor to destroy texture when gone..not using anymore probably
	~SpriteComponent()
	{
	
	}

	//set texture function taking in string id in assets to grab texture from its textures map so that we can set or swap textures
	void setTex(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void init() override
	{
		//sets our TransformComponent transform to our entities TransformComponent
		transform = &entity->getComponent<TransformComponent>();
		//we want to draw the whole image so we start from the beginning aka the top left of the img
		srcRect.x = srcRect.y = 0;
		//set our width to our transforms width which we already defined when we added our TransformComponent
		srcRect.w = transform->width;
		//set our height to our transforms width which we already defined when we added our TransformComponent
		srcRect.h = transform->height;
	}
	
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		//sets our sprites x position to the x position of the entity
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		//sets our sprites y position to the y position of the entity
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		//set up our scaled sprite img 
		destRect.w = transform->width * transform->wScale;
		//set up our scaled sprite img
		destRect.h = transform->height * transform->hScale;
	}
	//draws our sprite using the specified texture, pixel selection, and scaling, and sprite orientation via spriteFlip
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
	//changes current frames and index needed for changing animation
	void Play(const char* animName)
	{
		//cout << "down" << endl;
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};

