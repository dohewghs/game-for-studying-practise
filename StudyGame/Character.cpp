#include "Character.h"

Character::Character(Entity* _entity, IController* _controller) :
	entity(_entity),
	controller(_controller)
{
};

Character::Character(Character&& other) noexcept
{
	entity = other.entity;
	controller = other.controller;
	other.entity = nullptr;
	other.controller = nullptr;
}

Character& Character::operator=(Character&& other) noexcept
{
	if (this != &other)
	{
		delete entity; delete controller;
		entity = other.entity;
		controller = other.controller;
		other.entity = nullptr;
		other.controller = nullptr;
	}
	return *this;
}

Character::~Character()
{
	if (this->controller)
		delete controller;

	if (this->entity)
		delete entity;
}

Character::operator bool() const
{
	return (this->entity) && (this->controller);
}

void Character::present(SDL_Renderer* renderer)
{
	//std::cout << "Coords: " << entity->getHitBox().x << ' ' << entity->getHitBox().y << '\n';

	if (!this->entity)
		return;

	this->entity->present(renderer);
}

void Character::applyAcceleration(double deltaTime)
{
	if (!this->entity)
		return;

	this->entity->applyAcceleration(deltaTime);
}

void Character::handleInput()
{
	if (!this->controller || !this->entity)
		return;

	Vector2 inputDirection = this->controller->getInputDirection();

	this->entity->applySpeed(inputDirection);

	if (this->entity->isCanJump && this->controller->isJumpPressed())
	{
		Vector2 velocity = this->entity->getVelocity();
		velocity.y = -15;

		this->entity->setVelocity(velocity);
	}

	if (this->controller->isAttack())
	{
		this->entity->useWeapon();
	}
}

Entity* Character::getEntity()
{
	return this->entity;
}