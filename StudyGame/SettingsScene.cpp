#include "SettingsScene.h"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

void SettingsScene::present(SDL_Renderer*& renderer)
{
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();

    ImGui_ImplSDLRenderer3_RenderDrawData(draw_data, renderer);
}

void SettingsScene::update(float deltaTime)
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::SetWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(200, 150));

    if (ImGui::Button("Back", ImVec2(180, 40)))
    {
        this->nextState = AppState::menu;
    }

    ImGui::End();
}



AppState SettingsScene::handleInput()
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

void SettingsScene::setState(AppState state)
{
    this->nextState = state;
}
