#pragma once
#include "Components.h"
#include "../Vector2D.h"

//component class for getting, setting up, and updating x,y position of entities
//TransformComponent member function can take in x and y floast for position, ints for height and width and floats for width and height scaling
//form TransformComponent(float x, float y, int h, int w, float wscale, float hscale)    .... can also take just x and y floats
// TransformComponent(int h, int w, float wscale, float hscale, int winWidth = 1920, int winHeight = 1024)sets position of the entity in the center of the screen based on current settings of 1920x1024 and sets height, width and scaling use if not setting via Sprite
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
	
	int xvel = 0;
	int yvel = 0;
	
	//sets position of the entity
	TransformComponent()
	{
		//zero's out our position
		position.Zero();
	}

	// sets position of the entity in the center of the screen based on current settings of 1920x1024 and sets height, width and scaling use if not setting via Sprite
	TransformComponent(int h, int w, int wscale, int hscale, int winWidth=1920, int winHeight = 1024)
	{
		
		
		position.x = winWidth/ 2 - w/2 * wscale;
		position.y = winHeight/ 2 - h/2 * hscale;
		height = h;
		width = w;
		wScale = wscale;
		hScale = hscale;
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
		return sqrt(( velocity.x * velocity.x) + ( velocity.y * velocity.y));
	}
	//normalizes speed when applicable..no longer moves character for now due to tile scrolling implementation
	void normalize()
	{
		float m = mag(velocity.x, velocity.y);

		if (m > 1)
		{
			xvel = int((velocity.x * xspeed) / m);
			yvel = int((velocity.y * yspeed) / m);
			//position.x += xvel;
			//position.y += yvel;

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
		
	}


};