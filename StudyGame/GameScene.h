#pragma once
#include "IScene.h"
#include <vector>
#include "PhysicsEngine.h"
#include "Character.h"
#include "GameUI.h"
#include "Floor.h"

class GameScene : public IScene
{
	std::vector<Character> characters;
	PhysicsEngine engine;
	Floor thisfloor;

	GameUI HUD;

	AppState nextState;
	void centralizeAllToUser();
public:
	GameScene();
	~GameScene();

	void present(SDL_Renderer*& renderer) override;
	void update(float deltaTime) override;
	AppState handleInput() override;

	void setState(AppState state) override;
};