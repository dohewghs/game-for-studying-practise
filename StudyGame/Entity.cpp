#include "Entity.h"
#include "IController.h"
#include "Floor.h"

Entity::Entity() :
	hitBox(0, 0, 50, 50),
	rigidBody(&this->hitBox),
	statistics(),
	weapon(),
	contorller(nullptr),
	presenter(nullptr)
{
}

Entity::~Entity()
{
	delete this->contorller;
	delete this->presenter;
}

void Entity::move(Vector2 direction, float deltaTime)
{
	double speed = this->statistics.walkingSpeed;
	Vector2 movementForce = direction * speed;

	rigidBody.applyForce(movementForce);
}

void Entity::update(Vector2 additionalForce, float deltaTime)
{
	rigidBody.applyForce(additionalForce);

	if (!this->contorller)
		return;
	
	Vector2 inputDirection = this->contorller->getInputDirection();

	this->move(inputDirection, deltaTime);

	this->rigidBody.update(deltaTime);

}

void Entity::present()
{
	if (this->presenter)
	{
		this->presenter->present(this->hitBox);
	}
}

Rect& Entity::getHitBox() 
{
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