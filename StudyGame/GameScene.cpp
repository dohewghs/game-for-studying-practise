#include "GameScene.h"
#include "Character.h"
#include "UserController.h"
#include "ComputerController.h"
#include "BaseFloorPresenter.h"
#include "BaseEntityPresenter.h"
#include <iostream>

GameScene::GameScene() :
	characters(),
	engine(),
	HUD(),
	thisfloor(new BaseFloorPresenter)
{
	this->characters = std::vector<Character>(10);
	characters[0] = Character(new Entity(), new UserController());
	characters[1] = Character(new Entity(), new ComputerController());
}

GameScene::~GameScene() = default;

void GameScene::present(SDL_Renderer*& renderer)
{
	this->centralizeAllToUser();

	for (Character& character : this->characters)
	{
		character.present(renderer);
	}

	this->thisfloor.present(renderer);
}

void GameScene::update(float deltaTime)
{
	for (Character& character : this->characters)
	{
		character.applyAcceleration(deltaTime);

		Entity* entity = character.getEntity();
		if (!entity)
			continue;

		auto [coords, velocity] = this->engine.getAvailableMovement(*entity, this->thisfloor, deltaTime);

		entity->setPosition(coords);
		entity->setVelocity(velocity);

		entity->isCanJump = this->engine.canJump(*entity, this->thisfloor);

		if (entity->isUsingWeapon())
		{
			for (Character& character : this->characters)
			{
				Entity* enemy = character.getEntity();

				if (!enemy)
					continue;

				if (enemy == entity)
					continue;

				entity->attack(enemy);
			}
		}
	}
}

AppState GameScene::handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_ESCAPE)
			{
				return AppState::close;
			}
		}
	}

	for (Character& character : this->characters)
	{
		character.handleInput();
	}
	return AppState::game;
}


void GameScene::centralizeAllToUser()
{
	Vector2 center = { 200, 300 };

	Rect userHitBox = this->characters[0].getEntity()->getHitBox();

	Vector2 offset = { userHitBox.x, userHitBox.y };
	offset -= center;

	for (Character& character : this->characters)
	{
		Entity* entity = character.getEntity();

		if (!entity)
			continue;

		Rect hitBox = entity->getHitBox();
		Vector2 entityCoords = { hitBox.x, hitBox.y };
		entityCoords -= offset;

		entity->setPosition(entityCoords);
	}

	this->thisfloor.moveOn(offset*-1);
}