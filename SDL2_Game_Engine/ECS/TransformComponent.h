#pragma once
#include "ECS.h"


#include "../Vector2D.h"
//component class for getting, setting up, and updating x,y position of entities
class TransformComponent : public Component
{
private:
	
public:
	//create Vector2D called position which will hold the entities position
	Vector2D position;
	//vector2D for handling velocity of player
	Vector2D velocity;
	//interacts with velocity to adjust how fast the player moves
	float xspeed = 3;
	float yspeed = 3;
	TransformComponent(float x=0.0f, float y=0.0f)
	{
		position.x = x;
		position.y = y;
	}
	
	//like unity onAwake so as it starts up we set the x and y pos to 0
	/*void init() override
	{
		xpos = 0;
		ypos = 0;
	}*/
	//gets the magnitude
	float mag()
	{
		//getting the magnitude
		
		return sqrt(xspeed*xspeed*float(abs(velocity.x)) + yspeed * yspeed*float(abs(velocity.y)));
	
	}
	//normalizes speed when presses keys for x and y directions simultaneously but also lags game so i dont really want to touch it right now
	Vector2D normalize()
	{
		float m = mag();
		cout << m << endl;
		if (m > 0) {
			position.x += ((velocity.x*xspeed) / m);
			position.y += ((velocity.y*yspeed) / m);
			Vector2D newpos = Vector2D(position.x, position.y);
			cout << newpos << endl;
			return newpos;
		}
	}
	void init() override
	{
		//making sure we start at 0
		velocity.x = 0;
		//making sure we start at zero
		velocity.y = 0;
	}
	void update() override
	{	//updates positions with vector normalizing probably
		//normalize();
		//handles x position updates from movement
		position.x += velocity.x * xspeed;
		//handles y position updates from movement
		position.y += velocity.y * yspeed;
	}



};