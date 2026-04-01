#include "MenuScene.h"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

void MenuScene::present(SDL_Renderer*& renderer)
{
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();

    ImGui_ImplSDLRenderer3_RenderDrawData(draw_data, renderer);
}

void MenuScene::update(float deltaTime)
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::SetWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(200, 150));

    this->nextState = AppState::menu;

    if (ImGui::Button("Start Game", ImVec2(180, 40))) 
    {
        this->nextState = AppState::game;
    }

    if (ImGui::Button("Settings", ImVec2(180, 40))) 
    {
        this->nextState = AppState::settings;
    }

    if (ImGui::Button("Exit", ImVec2(180, 40))) 
    {
        this->nextState = AppState::close;
    }
    ImGui::End();

}

AppState MenuScene::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
        {
            return AppState::close;
        }
    }

    return this->nextState;
}