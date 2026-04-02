#include "Entity.h"
#include "IController.h"
#include "Floor.h"
#include <iostream>

Entity::Entity() :
	hitBox(0, 0, 50, 50),
	rigidBody(),
	statistics(),
	weapon()
{
}

Entity::~Entity() = default;

void Entity::update(Vector2 force, float deltaTime)
{
	rigidBody.applyForce(force);

	this->rigidBody.update(this->hitBox, deltaTime);
}

Rect& Entity::getHitBox() 
{
	std::cout << "method Entity::getHitBox() " << std::endl;
	return this->hitBox;
}

Rect Entity::getHitBox() const
{
	return this->hitBox;
}

void Entity::setVelocityY(double value)
{
	this->rigidBody.setVelocityY(value);
}