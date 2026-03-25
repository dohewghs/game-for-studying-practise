#include "Entity.h"
#include "IController.h"
#include "Floor.h"

Entity::Entity() :
	hitBox(0, 0, 50, 50),
	rigidBody(&this->hitBox),
	statistics(),
	weapon(),
	presenter(nullptr)
{
}

Entity::~Entity()
{
	delete this->presenter;
}

void Entity::update(Vector2 force, float deltaTime)
{
	rigidBody.applyForce(force);

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