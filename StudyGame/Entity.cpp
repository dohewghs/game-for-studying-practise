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