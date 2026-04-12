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

	void applyAcceleration(double deltaTime)
	{
		this->velocity += acceleration * deltaTime;
		this->velocity.x *= 0.98;

		acceleration = { 0,0 };
	}

	void setVelocity(Vector2 value)
	{
		this->velocity = value;
	}

	Vector2 getVelocity() const
	{
		return this->velocity;
	}
};