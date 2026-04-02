#pragma once
#include "IScene.h"
#include "IController.h"
#include <vector>
#include "PhysicsEngine.h"
#include "Entity.h"
#include "GameUI.h"
#include "Floor.h"

class GameScene : public IScene
{
	struct Character
	{
		Entity* entity = nullptr;
		IController* controller = nullptr;
		IEntityPresenter* presenter = nullptr;

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
	};

	std::vector<Character> characters;
	PhysicsEngine engine;
	Floor thisfloor;

	GameUI HUD;

	std::vector<Entity*> getEntities();
public:
	GameScene();
	~GameScene();

	void present(SDL_Renderer*& renderer) override;
	void update(float deltaTime) override;
	AppState handleInput() override;

};