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
    ImGui::SetWindowSize(ImVec2(300, 400)); // Трохи збільшив для зручності

    ImGui::Text("Key Bindings:");
    ImGui::Separator();

    const char* labels[] = { "Left", "Right", "Jump", "Attack", "Interaction" };

    for (int i = 0; i <= (int)InputManager::direction::interaction; ++i)
    {
        InputManager::direction dir = (InputManager::direction)i;
        ImGui::PushID(i);

        ImGui::Text("%s:", labels[i]);
        ImGui::SameLine(100);

        if (selectedControl == i) 
        {
            ImGui::Button("Waiting...", ImVec2(120, 0));
        }
        else 
        {
            if (ImGui::Button(inputManager->getKeyName(dir), ImVec2(120, 0))) 
            {
                selectedControl = i;
            }
        }
        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Back", ImVec2(280, 40)))
    {
        this->nextState = AppState::menu;
        selectedControl = -1; // Скидаємо вибір при виході
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

        if (selectedControl != -1 && event.type == SDL_EVENT_KEY_DOWN)
        {
            SDL_Scancode newKey = event.key.scancode;

            // Тут викликай свій InputManager, щоб зберегти нову клавішу
            // Наприклад: inputManager.setKey(selectedControl, newKey);
            this->inputManager->setKey((InputManager::direction)selectedControl, newKey);

            SDL_Log("Action %d bound to key: %s", selectedControl, SDL_GetScancodeName(newKey));

            selectedControl = -1;
        }
    }

    return this->nextState;
}

void SettingsScene::setState(AppState state)
{
    this->nextState = state;
}
