#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include<map>;
class SpriteComponent: public Component
{
private:
	//reference to the position of the sprite
	TransformComponent *transform;
	//texture for the sprite 
	SDL_Texture *texture;
	//rects for sizing and scaling sprite
	SDL_Rect srcRect, destRect;
	//are we animated?
	bool animated = false;
	//# of frames
	int frames = 0;
	//delat between frames in miliseconds
	int speed = 100;
	
public:

	int animIndex = 0;

	SpriteComponent() = default;
	//hold animations, taking in animation name, and an Animation object called animations
	std::map<const char*, Animation> animations;
	
	//create sprite component based path to texture img, starting img render points, number of horizontalxvertical pixels of source to render, and scaling
	SpriteComponent(const char* path)
	{
		//creates texture by loading our image using setTex function defined after our function here
		setTex(path);
	
	}

	//create sprite component uaing path to texture img, and whether its animated or not 
	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 15, 50);
		Animation blast = Animation(1, 15, 100);
		Animation rollRight = Animation(2, 5, 50);
		Animation rollLeft = Animation(3, 5, 50);
		Animation rollUp = Animation(5, 5, 50);
		Animation rollDown = Animation(4, 5, 50);
		animations.emplace("Idle", idle);
		animations.emplace("Blast", blast);
		animations.emplace("RollRight", rollRight);
		animations.emplace("RollLeft", rollLeft);
		animations.emplace("RollUp", rollUp);
		animations.emplace("RollDown", rollDown);

		
		setTex(path);
		Play("Idle");

	}

	//deconstructor to destroy texture when gone
	~SpriteComponent()
	{
		//destroying our texture
		SDL_DestroyTexture(texture);
	}

	//set texture function taking in a path to a img so that we can set or swap textures
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
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
		destRect.x = static_cast<int>(transform->position.x);
		//sets our sprites y position to the y position of the entity
		destRect.y = static_cast<int>(transform->position.y);
		//set up our scaled sprite img 
		destRect.w = transform->width * transform->wScale;
		//set up our scaled sprite img
		destRect.h = transform->height * transform->hScale;
	}
	//draws our sprite using the specified texture, pixel selection, and scaling
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
	//changes current frames and index needed for changing animation
	void Play(const char* animName)
	{
		cout << "bob" << endl;
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};

