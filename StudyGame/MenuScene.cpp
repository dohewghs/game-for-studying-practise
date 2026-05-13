#include "MenuScene.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include "ResourceManager.h"

MenuScene::MenuScene(InputManager* manager) :
    IScene(manager),
    nextState(AppState::menu)
{
}

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

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoScrollbar;

    // Центруємо вікно ImGui
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(250, 400));

    ImGui::Begin("Main Menu", nullptr, window_flags);

    // 1. Стилізація: прибираємо фони та рамки стандартних кнопок ImGui
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.2f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

    ImVec2 buttonSize(200, 60);
    SDL_Texture* tex = ResourceManager::getTexture("menu_button");

    // UV-координати для кнопки (як ми розрахували раніше)
    float tw = 640.0f; float th = 512.0f;
    ImVec2 uv0 = ImVec2(256.0f / tw, 416.0f / th);
    ImVec2 uv1 = ImVec2((256.0f + 64.0f) / tw, (416.0f + 32.0f) / th);

    // Масив з назвами кнопок та станами для зручності
    struct Btn { const char* label; AppState target; };
    Btn buttons[] = {
        {"Start Game", AppState::game},
        {"Settings",   AppState::settings},
        {"Exit",       AppState::close}
    };

    for (int i = 0; i < 3; i++) {
        ImGui::PushID(i); // Щоб ImGui не плутав кнопки

        // Малюємо саму картинку як кнопку
        if (ImGui::ImageButton("##btn", (ImTextureID)tex, buttonSize, uv0, uv1)) {
            this->nextState = buttons[i].target;
        }

        // --- ЛОГІКА НАКЛАДАННЯ ТЕКСТУ ---
        // Отримуємо координати щойно намальованої кнопки
        ImVec2 bMin = ImGui::GetItemRectMin();
        ImVec2 bMax = ImGui::GetItemRectMax();

        // Розраховуємо центр
        ImVec2 textSize = ImGui::CalcTextSize(buttons[i].label);
        ImVec2 textPos = ImVec2(
            bMin.x + (buttonSize.x - textSize.x) * 0.5f,
            bMin.y + (buttonSize.y - textSize.y) * 0.5f
        );

        // Малюємо текст поверх кнопки (білим кольором)
        ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), buttons[i].label);

        ImGui::PopID();
        ImGui::Spacing(); // Відступ між кнопками
    }

    // Повертаємо стилі назад
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

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

void MenuScene::setState(AppState state)
{
    this->nextState = state;
}
