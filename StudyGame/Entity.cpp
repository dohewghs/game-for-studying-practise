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
	return this->hitBox;
}

Rect Entity::getHitBox() const
{
	return this->hitBox;
}

RigidBody& Entity::getRigiBody()
{
	return this->rigidBody;
}

void Entity::applyImpulse(Vector2 force) 
{
	rigidBody.applyForce(force);
}

void Entity::applySpeed(Vector2 direction)
{
	rigidBody.applyForce(direction * this->statistics.walkingSpeed);
}

