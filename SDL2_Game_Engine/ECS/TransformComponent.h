#pragma once
#include "Components.h"
#include "../Vector2D.h"
//component class for getting, setting up, and updating x,y position of entities
//TransformComponent member function can take in x and y floast for position, ints for height and width and floats for width and height scaling
//form TransformComponent(float x, float y, int h, int w, float wscale, float hscale)    .... can also take just x and y floats
class TransformComponent : public Component
{
private:
	
public:
	//create Vector2D called position which will hold the entities position
	Vector2D position;
	//vector2D for handling velocity of player
	Vector2D velocity;

	//height and width values for hit/collider box
	int height = 2;
	int	width = 2;
	//scaling the hit/collider box
	int wScale = 1, hScale =1;
	
	
	//interacts with velocity to adjust how fast the player moves
	int xspeed = 5;
	int yspeed = 3;
	
	
	
	//sets position of the entity
	TransformComponent()
	{
		//zero's out our position
		position.Zero();
	}

	// sets position of the entity as well as height, width and scaling use if not setting via Sprite
	TransformComponent(float x , float y , int h, int w, int wscale, int hscale)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		wScale = wscale;
		hScale = hscale;
	}


	//gets the magnitude
	float mag(float xvel, float yvel)
	{

		//getting the magnitude
		//return sqrt((xspeed * velocity.x * velocity.x) + (yspeed * velocity.y * velocity.y));
		return sqrt(( velocity.x * velocity.x) + ( velocity.y * velocity.y));
	}
	//normalizes speed when presses keys for x and y directions simultaneously but also lags game so i dont really want to touch it right now
	void normalize()
	{
		float m = mag(velocity.x, velocity.y);

		if (m > 1)
		{
			position.x += int((velocity.x * xspeed) / m);
			position.y += int((velocity.y * yspeed) / m);

		}
	}
	void init() override
	{
		//making sure we start at 0
		velocity.Zero();
	}
	void update() override
	{	//updates positions with vector normalizing probably
		normalize();
		//handles x position updates from movement
		//position.x += velocity.x * xspeed;
		//handles y position updates from movement
		//position.y += velocity.y * yspeed;
	}


};