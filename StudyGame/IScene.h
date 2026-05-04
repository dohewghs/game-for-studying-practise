#pragma once
#include <SDL3/SDL_render.h>
#include "AppState.h"
#include "InputManager.h"

class IScene
{
protected:
	InputManager* inputManager;

	IScene(InputManager* manager)
	{
		this->inputManager = manager;
	}
public:
	virtual ~IScene() = default;

	virtual void present(SDL_Renderer*& renderer) = 0;
	virtual void update(float deltaTime) = 0;
	virtual AppState handleInput() = 0;

	virtual void setState(AppState state) = 0;
};