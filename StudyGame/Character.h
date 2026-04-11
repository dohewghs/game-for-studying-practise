#pragma once
#include "Entity.h"

class Character
{
private:
	Entity* entity = nullptr;
	IController* controller = nullptr;
	IEntityPresenter* presenter = nullptr;
public:
	Character(Entity* _entity = nullptr, IController* _controller = nullptr, IEntityPresenter* _presenter = nullptr) :
		entity(_entity),
		controller(_controller),
		presenter(_presenter)
	{
	};

	Character(const Character& other) = delete;

	Character(Character&& other) noexcept
	{
		entity = other.entity;
		controller = other.controller;
		presenter = other.presenter;
		other.entity = nullptr;
		other.controller = nullptr;
		other.presenter = nullptr;
	}

	Character& operator=(Character&& other) noexcept
	{
		if (this != &other)
		{
			delete entity; delete controller; delete presenter;
			entity = other.entity;
			controller = other.controller;
			presenter = other.presenter;
			other.entity = nullptr;
			other.controller = nullptr;
			other.presenter = nullptr;
		}
		return *this;
	}

	~Character()
	{
		if (this->controller)
			delete controller;

		if (this->presenter)
			delete presenter;

		if (this->entity)
			delete entity;
	}

	operator bool() const
	{
		return (this->entity) && (this->controller) && (this->presenter);
	}

	void present(SDL_Renderer* renderer)
	{
		if (!*this)
			return;

		this->presenter->present(renderer, this->entity);
	}

	void update(double deltaTime)
	{
		if (!this->entity)
			return;

		this->entity->update(deltaTime);
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
			this->entity->setVelocityY(-15);
		}
	}

	Entity* getEntity()
	{
		return this->entity;
	}
};