#pragma once
#include "Entity.h"

class Character
{
private:
	Entity* entity = nullptr;
	IController* controller = nullptr;

public:
	Character(Entity* _entity = nullptr, IController* _controller = nullptr, IEntityPresenter* _presenter = nullptr) :
		entity(_entity),
		controller(_controller)
	{
	};

	Character(const Character& other) = delete;

	Character(Character&& other) noexcept
	{
		entity = other.entity;
		controller = other.controller;
		other.entity = nullptr;
		other.controller = nullptr;
	}

	Character& operator=(Character&& other) noexcept
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

	~Character()
	{
		if (this->controller)
			delete controller;

		if (this->entity)
			delete entity;
	}

	operator bool() const
	{
		return (this->entity) && (this->controller);
	}

	void present(SDL_Renderer* renderer)
	{
		if (!this->entity)
			return;

		this->entity->present(renderer);
	}

	void applyAcceleration(double deltaTime)
	{
		if (!this->entity)
			return;

		this->entity->applyAcceleration(deltaTime);
	}

	void handleInput()
	{
		if (!this->controller || !this->entity)
			return;

		Vector2 inputDirection = this->controller->getInputDirection();

		this->entity->applySpeed(inputDirection);

		std::cout << "Coords: " << entity->getHitBox().x << ' ' << entity->getHitBox().y << '\n';

		if (this->entity->isCanJump && this->controller->isJumpPressed())
		{
			Vector2 velocity = this->entity->getVelocity();
			velocity.y = -15;

			this->entity->setVelocity(velocity);
		}

		if (this->controller->isAttack())
		{
			std::cout << "here-------------\n";
			this->entity->useWeapon();
		}
	}

	Entity* getEntity()
	{
		return this->entity;
	}
};