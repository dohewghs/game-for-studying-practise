#include "MenuScene.h"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

void MenuScene::present(SDL_Surface*& surface)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT) 
        {
            // logic to close app
        }
    }
}

void MenuScene::update(float deltaTime)
{
    
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Крок 3: Описуємо інтерфейс меню
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::SetWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(200, 150));

    if (ImGui::Button("Start Game", ImVec2(180, 40))) 
    {
        // Тут логіка переходу: sceneManager->changeScene(new GameScene());
    }

    if (ImGui::Button("Settings", ImVec2(180, 40))) 
    {
        // sceneManager->changeScene(new SettingsScene());
    }

    if (ImGui::Button("Exit", ImVec2(180, 40))) 
    {
        exit(0);
    }

    ImGui::End();
}

void MenuScene::handleInput()
{
    ImGui::Render();
}