#pragma once
#include"ECS.h"
#include "Components.h"
#include "../Vector2D.h"
#include <math.h>
//holds the names of our projectiles
static std::string projectiles[100] = { "slime_ki_blast" };
//constructor takes in range, speed, and vector2D velocity
class ProjectileComponent : public Component
{
public:
	
	Vector2D initPosition;
	bool isAnimated = true;
	int range = 0;
	int speed = 0;
	int distance = 0;
	int projectileIndex = 0;
	TransformComponent* transform;
	Vector2D velocity;
	//takes in range and speed ints
	ProjectileComponent(Vector2D pos, int rng, int sp, int velX, int velY, int pIndex, bool isAnim) 
	{
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
		//for now just for fun we will make a new one even though it's gonna be resource intensive
		Vector2D initPos = entity->getComponent<ProjectileComponent>().initPosition;
		bool isAnimated = entity->getComponent<ProjectileComponent>().isAnimated;

		int range = entity->getComponent<ProjectileComponent>().range;
		int speed = entity->getComponent<ProjectileComponent>().speed;

		int projectileIndex = entity->getComponent<ProjectileComponent>().projectileIndex;
		Vector2D velocity = entity->getComponent<ProjectileComponent>().velocity;

		Game::assets->CreateProjectile(initPos, velocity, range, speed, projectileIndex, isAnimated);
		cout << "we should have created something" << endl;
		entity->destroy();
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
		cout << distance << endl;
		if (distance > range)
		{
			std::cout << "out of range" << endl;
			resetProjectile(entity);
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			std::cout << "exited bounds!" << endl;
			resetProjectile(entity);
		}
	}
private:
	

};