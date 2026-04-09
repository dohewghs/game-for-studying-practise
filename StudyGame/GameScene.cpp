#include "GameScene.h"
#include "UserController.h"
#include "BaseFloorPresenter.h"
#include "BaseEntityPresenter.h"
#include <iostream>

std::vector<Entity*> GameScene::getEntities()
{
	std::vector<Entity*> res = std::vector<Entity*>();

	for (Character& character : this->characters)
	{
		if (character)
			res.push_back(character.entity);
	}

	return res;
}

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
		if (character)
			character.presenter->present(renderer, character.entity);
	}

	this->thisfloor.present(renderer);
}

void GameScene::update(float deltaTime)
{
	std::vector<Entity*> entities = this->getEntities();

	this->engine.update(entities, this->thisfloor, 0.1);

	
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

	for (const Character& character : this->characters)
	{
		if (character)
		{
			Vector2 input = character.controller->getInputDirection();
			//std::cout << "input direction: " << input.x << ' ' << input.y << std::endl;
			this->engine.handleInput(*character.entity, input, this->thisfloor);
		}
	}
	return AppState::game;
}
