#include "main.h"



int main(int argc, char* argv[]) 
{
    //std::cout << std::filesystem::current_path() << '\n';

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Test", 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    // ЗАМІСТЬ IMG_Init — спробуйте відразу завантажити текстуру
    // Навіть якщо файлу немає, ми перевіримо, чи знає компілятор цю функцію
    SDL_Texture* texture = IMG_LoadTexture(renderer, "..//..//..//..//assets//test//test.png");

    SDL_Log("Error: %s", SDL_GetError());

    if (texture == NULL) 
    {
        // Це нормально, якщо файлу немає. Головне — щоб тут не було помилки 'identifier not found'
        SDL_Log("IMG_LoadTexture finded!");
    }

    while (true)
    {
        SDL_SetRenderDrawColor(renderer, 30, 30, 100, 255);
        SDL_RenderClear(renderer);

        // Малюємо нашу текстуру
        if (texture) 
        {
            SDL_FRect rect = { 0,0,300,300 };
            SDL_RenderTexture(renderer, texture, NULL, &rect);
        }

        // Показуємо результат на екрані
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}