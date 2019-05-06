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
	float xspeed = 30;
	float yspeed = 30;
	TransformComponent(float x = 0.0f, float y = 0.0f);
	
	
	
	//gets the magnitude
	float mag(float xvel, float yvel);
	
		
		
	
	//normalizes speed when presses keys for x and y directions simultaneously but also lags game so i dont really want to touch it right now
	void normalize();
	//makes sure velocity starts at zero or whatever it should be once gravity exists
	void init() override;
	//updates position
	void update() override;
	



};