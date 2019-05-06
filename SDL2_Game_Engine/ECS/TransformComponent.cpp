#pragma once
#include "TransformComponent.h"



	
	
	//sets position of the entity
	TransformComponent::TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	
	//gets the magnitude
	float TransformComponent:: mag(float xvel, float yvel)
	{

		//getting the magnitude
		return sqrt((xspeed * velocity.x * velocity.x) +  (yspeed * velocity.y * velocity.y));

	}
	//normalizes speed when presses keys for x and y directions simultaneously but also lags game so i dont really want to touch it right now
	void TransformComponent:: normalize()
	{
		float m = mag(velocity.x,velocity.y);
		
		if (m>1) 
		{
			position.x += int((velocity.x*xspeed) / m);
			position.y += int((velocity.y*yspeed) / m);
			
		}
	}
	void TransformComponent::init() 
	{
		//making sure we start at 0
		velocity.x = 0;
		//making sure we start at 0
		velocity.y = 0;
	}
	void TransformComponent::update() 
	{	//updates positions with vector normalizing probably
		normalize();
		//handles x position updates from movement
		//position.x += velocity.x * xspeed;
		//handles y position updates from movement
		//position.y += velocity.y * yspeed;
	}



