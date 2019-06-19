#pragma once
#include"ECS.h"
#include "Components.h"
#include "../Vector2D.h"
#include <math.h>

//holds the names of our projectiles
static std::string projectiles[100] = { "slime_ki_blast" ,"PlayerFGHB"};
//constructor takes in range, speed, and vector2D velocity
class ProjectileComponent : public Component
{
public:
	
	Vector2D initPosition;
	bool isAnimated = true;
	int xScale = 1;
	int yScale = 1;
	int range = 0;
	int speed = 0;
	int distance = 0;
	int projectileIndex = 0;
	
	TransformComponent* transform;
	Vector2D velocity;
	ProjectileComponent()
	{
		
	}

	//takes in range and speed ints
	ProjectileComponent(Vector2D pos, int xscale, int yscale, int rng, int sp, int velX, int velY, int pIndex, bool isAnim) 
	{
		yScale = yscale;
		xScale = xscale;
		initPosition = pos;
		range = rng; 
		speed = sp;
		velocity.x = velX;
		velocity.y = velY;
		projectileIndex = pIndex;
		isAnimated = isAnim;
		
	};
	~ProjectileComponent()
	{

	}
	//function that tries to re-instantiate projectile as it was initially
	void resetProjectile(Entity* projectile)
	{
		
		entity = projectile;
		
		entity->destroy();
		
		//for now just for fun we will make a new one even though it's gonna be resource intensive
		Game::assets->CreateProjectile(projectile->getComponent<ProjectileComponent>().initPosition
			, projectile->getComponent<ProjectileComponent>().velocity
			, projectile->getComponent<ProjectileComponent>().xScale
			, projectile->getComponent<ProjectileComponent>().yScale
			, projectile->getComponent<ProjectileComponent>().range
			, projectile->getComponent<ProjectileComponent>().speed
			, projectile->getComponent<ProjectileComponent>().projectileIndex
			, projectile->getComponent<ProjectileComponent>().isAnimated);
		
		
		
		
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		transform->xspeed = transform->yspeed = speed;
	}

	void update() override
	{
		//literal distance formula from vector2D coordinates current and initial
		distance = int ( abs( sqrt( pow((transform->position.x - initPosition.x),2) + pow((transform->position.x - initPosition.x),2) ) ) );
		//cout << distance << endl;
		if (distance > range)
		{
			//std::cout << "out of range" << endl;
			resetProjectile(entity);
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			//std::cout << "exited bounds!" << endl;
			resetProjectile(entity);
		}
	}
private:
	

};