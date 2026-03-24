#pragma once

#include "Vector2.h"
#include "Rect.h"
#include <memory>

class Rect;

class RigidBody
{
private:
	Rect* hitBox;

	Vector2 velocity;
	Vector2 acceleration;

public:
	RigidBody(Rect* _hitbox = nullptr) :
		hitBox(_hitbox),
		velocity(0,0),
		acceleration(0,0)
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

		hitBox->x += velocity.x * deltaTime;
		hitBox->y += velocity.y * deltaTime;

		acceleration = Vector2(0, 0);
	}

	void setVelocity(double value)
	{
		this->velocity = value;
	}
};