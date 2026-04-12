#include "GameScene.h"
#include "Character.h"
#include "UserController.h"
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
	characters[0] = Character(new Entity(), new UserController(), new BaseEntityPresenter());
}

GameScene::~GameScene() = default;

void GameScene::present(SDL_Renderer*& renderer)
{
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
