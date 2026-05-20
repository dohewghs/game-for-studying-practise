#include "App.h"
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_stdlib.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>

App::App(SDL_Window* _window, SDL_Renderer* _renderer) :
	window(_window),
	renderer(_renderer),

	scenesManager()
{
	ImGui::CreateContext();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);	
}

App::~App()
{
	this->window = nullptr;
	this->renderer = nullptr;
}

void App::run()
{
	bool isRunning = true;

	uint64_t lastTime = SDL_GetTicks();
	while (isRunning)
	{
		uint64_t currentTime = SDL_GetTicks();
		// Рахуємо різницю в мілісекундах і переводимо в секунди
		double deltaTime = static_cast<double>(currentTime - lastTime);
		lastTime = currentTime;

		// Захист від заїдань (якщо вікно перетягували, deltaTime не має бути гігантським)
		if (deltaTime > 0.1) 
			deltaTime = 0.1;

		IScene* currentScene = this->scenesManager.getScene();

		AppState state = currentScene->handleInput();

		if (state == AppState::close)
		{
			isRunning = false;
			std::cout << "End app" << std::endl;

			break;
		}

		currentScene->update(0.016);

		this->scenesManager.changeScene(state);

		SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
		SDL_RenderClear(renderer); // ОБОВ'ЯЗКОВО ПЕРЕД PRESENT

		currentScene->present(renderer);

		SDL_RenderPresent(renderer);
	}
}

void App::init()
{
	ResourceManager::init(this->renderer);

	ResourceManager::loadTexture("hero_idle", "..//..//..//..//assets//FREE_Samurai_2D//Sprites//IDLE.png");
	ResourceManager::loadTexture("Character Run", "..//..//..//..//assets//FREE_Samurai_2D//Sprites//RUN.png");
	ResourceManager::loadTexture("hurt", "..//..//..//..//assets//FREE_Samurai_2D//Sprites//HURT.png");

	ResourceManager::loadTexture("health_atlas", "..//..//..//..//assets//Pixel_UI_pack_3//07.png");

	ResourceManager::loadTexture("menu_button", "..//..//..//..//assets//Pixel_Buttom.png");

	ResourceManager::loadTexture("world_tileset", "..//..//..//..//assets//brackeys_platformer_assets//sprites//world_tileset.png");

	this->scenesManager.MakeScenes();
}
