#pragma once
#include "IScene.h"

class MenuScene : public IScene
{
	AppState nextState;
public:
	MenuScene(InputManager* manager);
	~MenuScene() = default;

	void present(SDL_Renderer*& renderer) override;
	void update(float deltaTime) override;
	AppState handleInput() override;

	void setState(AppState state) override;
};