#include "Entity.h"
#include "IController.h"
#include "Floor.h"

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

Vector2 Entity::getVelocity() const
{
	return this->rigidBody.getVelocity();
}

void Entity::setVelocityY(double value)
{
	this->rigidBody.setVelocityY(value);
}

void Entity::setVelocityX(double value)
{
	this->rigidBody.setVelocityX(value);
}