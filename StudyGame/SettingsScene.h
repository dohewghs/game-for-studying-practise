#pragma once
#include "IScene.h"

class SettingsScene : public IScene
{
private:
	AppState nextState;
	int selectedControl = -1;

public:
	SettingsScene(InputManager* manager) :
		IScene(manager),
		nextState(AppState::settings)
	{ }

	~SettingsScene() = default;

	void present(SDL_Renderer*& renderer) override;
	void update(float deltaTime) override;
	AppState handleInput() override;
	void setState(AppState state) override;
};