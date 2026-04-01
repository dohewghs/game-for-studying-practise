#include "main.h"
#include "App.h"


int main(int argc, char* argv[]) 
{
    //std::cout << std::filesystem::current_path() << '\n';
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); // або "direct3d11" для Windows

    SDL_Window* window = SDL_CreateWindow("Test", 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    App app(window, renderer);
    app.run();

    //while (true)
    //{
    //    SDL_SetRenderDrawColor(renderer, 30, 30, 100, 255);
    //    SDL_RenderClear(renderer);

    //    // Малюємо нашу текстуру
    //    if (texture) 
    //    {
    //        SDL_FRect rect = { 0,0,300,300 };
    //        SDL_RenderTexture(renderer, texture, NULL, &rect);
    //    }

    //    // Показуємо результат на екрані
    //    SDL_RenderPresent(renderer);
    //}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}