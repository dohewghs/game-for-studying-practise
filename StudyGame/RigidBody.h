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

	void applyForce(const Vector2& force) 
	{
		this->acceleration.x += force.x; 
		this->acceleration.y += force.y;
	}

	void update(Rect& hitBox, float deltaTime)
	{
		velocity += acceleration * deltaTime;
		velocity *= 0.99;
		std::cout << "velocity: " << velocity.x << ' ' << velocity.y << std::endl;
		hitBox.x += velocity.x * deltaTime;
		hitBox.y += velocity.y * deltaTime;

		acceleration = Vector2(0, 0);
	}

	void setVelocityY(double value)
	{
		this->velocity.y = value;
	}
};