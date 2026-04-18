#pragma once
#include "IScene.h"

class SettingsScene : public IScene
{
private:
	AppState nextState;

public:
	SettingsScene() :
		nextState(AppState::settings)
	{ }

	~SettingsScene() = default;

	void present(SDL_Renderer*& renderer) override;
	void update(float deltaTime) override;
	AppState handleInput() override;
	void setState(AppState state) override;
};