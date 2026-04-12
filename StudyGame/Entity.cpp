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

void Entity::applyAcceleration(double deltaTime)
{
	this->rigidBody.applyAcceleration(deltaTime);
}

Rect& Entity::getHitBox() {	return this->hitBox; }

Rect Entity::getHitBox() const
{
	return this->hitBox;
}

RigidBody& Entity::getRigiBody()
{
	return this->rigidBody;
}

void Entity::applySpeed(Vector2 direction)
{
	rigidBody.setAcceleration(direction * this->statistics.walkingSpeed);
}

Vector2 Entity::getVelocity() const
{
	return this->rigidBody.getVelocity();
}

void Entity::setVelocity(Vector2 _velocity)
{
	this->rigidBody.setVelocity(_velocity);
}

void Entity::setPosition(Vector2 position)
{
	this->hitBox.x = position.x;
	this->hitBox.y = position.y;
}
