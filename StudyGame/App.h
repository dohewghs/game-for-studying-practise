#pragma once
#include "SceneManager.h"
#include "MenuScene.h"
#include <SDL3/SDL.h>
#include <vector>
#include "AppState.h"

class App
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	SceneManager scenesManager;
	InputManager* inputKeysManager;

public:
	App(SDL_Window* _window, SDL_Renderer* _renderer);

	~App();

	void run();


};