#pragma once

#include "Vector2.h"
#include "Rect.h"
#include <memory>
#include <iostream>

class Rect;

class RigidBody
{
private:
	Vector2 velocity;
	Vector2 acceleration;

public:
	RigidBody() :
		velocity(0,0),
		acceleration(0,0)
	{
	}

	void setAcceleration(const Vector2& force) 
	{
		this->acceleration.x += force.x; 
		this->acceleration.y += force.y;
	}

	void update(double deltaTime)
	{
		this->velocity += acceleration * deltaTime;
		this->velocity.x *= 0.98;

		acceleration = { 0,0 };
	}

	void setVelocityY(double value)
	{
		this->velocity.y = value;
	}

	void setVelocityX(double value)
	{
		this->velocity.x = value;
	}

	Vector2 getVelocity() const
	{
		return this->velocity;
	}
};