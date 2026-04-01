#include "App.h"
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_stdlib.h>
#include <iostream>

App::App(SDL_Window* _window, SDL_Renderer* _renderer) :
	window(_window),
	renderer(_renderer),

	scenesManager()
{
	ImGui::CreateContext();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);	
	
	this->scenesManager.MakeScenes();
}

App::~App()
{
	this->window = nullptr;
	this->renderer = nullptr;
}

void App::run()
{
	bool isRunning = true;

	while (isRunning)
	{
		AppState state = this->scenesManager.getScene()->handleInput();

		this->scenesManager.getScene()->update(0.1);

		if (state == AppState::close)
		{
			isRunning = false;
			std::cout << "End app" << std::endl;
		}
		this->scenesManager.changeScene(state);

		SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
		SDL_RenderClear(renderer); // ÎÁÎÂ'ßÇÊÎÂÎ ÏÅÐÅÄ PRESENT

		this->scenesManager.getScene()->present(renderer);

		SDL_RenderPresent(renderer);
	}
}
