#pragma once

#include "Vector2.h"
#include "Rect.h"
#include <memory>

class Rect;

class RigidBody
{
private:
	Rect* hitBox;
	double gravityScale;

	Vector2 velocity;
	Vector2 acceleration;
	double friction;

public:
	RigidBody(Rect* _hitbox = nullptr) :
		hitBox(_hitbox),
		gravityScale(1),
		velocity(0,0),
		acceleration(0,0),
		friction(0.1)
	{
	}

	void applyForce(const Vector2& force) 
	{
		this->acceleration.x += force.x; 
		this->acceleration.y += force.y;
	}

	void update(float deltaTime)
	{
		velocity += acceleration * deltaTime;
		velocity *= (1 - this->friction);


		hitBox->x += velocity.x * deltaTime;
		hitBox->y += velocity.y * deltaTime;

		acceleration = Vector2(0, 0);
	}


};