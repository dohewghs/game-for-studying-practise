#include "SettingsScene.h"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include "ResourceManager.h"

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

    // Прапорці для прозорого та фіксованого вікна
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoCollapse;

    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, 500));

    ImGui::Begin("Settings", nullptr, window_flags);

    // Текстура та координати (ті самі, що й для головного меню)
    SDL_Texture* tex = ResourceManager::getTexture("menu_button");
    float tw = 640.0f; float th = 512.0f;
    ImVec2 uv0 = ImVec2(256.0f / tw, 416.0f / th);
    ImVec2 uv1 = ImVec2((256.0f + 64.0f) / tw, (416.0f + 32.0f) / th);

    // Стилізація ImGui (прибираємо сині рамки)
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.2f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

    ImGui::Text("Key Bindings:");
    ImGui::Separator();
    ImGui::Spacing();

    const char* labels[] = { "Left", "Right", "Jump", "Attack", "Interaction" };
    ImVec2 keyBtnSize(150, 40); // Трохи менші кнопки для списку клавіш

    for (int i = 0; i <= (int)InputManager::direction::interaction; ++i)
    {
        InputManager::direction dir = (InputManager::direction)i;
        ImGui::PushID(i);

        ImGui::AlignTextToFramePadding(); // Вирівнюємо текст по вертикалі з кнопкою
        ImGui::Text("%s:", labels[i]);
        ImGui::SameLine(120);

        // Визначаємо текст, який буде на кнопці
        const char* buttonLabel = (selectedControl == i) ? "Waiting..." : inputManager->getKeyName(dir);

        // Малюємо кнопку-картинку
        if (ImGui::ImageButton("##keybtn", (ImTextureID)tex, keyBtnSize, uv0, uv1))
        {
            selectedControl = i;
        }

        // Накладаємо назву клавіші поверх кнопки
        ImVec2 bMin = ImGui::GetItemRectMin();
        ImVec2 textSize = ImGui::CalcTextSize(buttonLabel);
        ImVec2 textPos = ImVec2(
            bMin.x + (keyBtnSize.x - textSize.x) * 0.5f,
            bMin.y + (keyBtnSize.y - textSize.y) * 0.5f
        );
        ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), buttonLabel);

        ImGui::PopID();
        ImGui::Spacing();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Кнопка Back (велика)
    ImVec2 backBtnSize(280, 50);
    if (ImGui::ImageButton("##back", (ImTextureID)tex, backBtnSize, uv0, uv1))
    {
        this->nextState = AppState::menu;
        selectedControl = -1;
    }

    // Текст для кнопки Back
    ImVec2 bMin = ImGui::GetItemRectMin();
    ImVec2 bSize = ImGui::GetItemRectSize();
    ImVec2 tSize = ImGui::CalcTextSize("Back");
    ImGui::GetWindowDrawList()->AddText(
        ImVec2(bMin.x + (bSize.x - tSize.x) * 0.5f, bMin.y + (bSize.y - tSize.y) * 0.5f),
        IM_COL32(255, 255, 255, 255), "Back"
    );

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

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
