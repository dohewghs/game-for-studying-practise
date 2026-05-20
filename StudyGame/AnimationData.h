#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

struct AnimationData
{
    struct AnimationState
    {
        int total_frames = 1;
        
        double animation_duration = 0.5;

        int current_frame = 0;
        double time_accumulator = 0.0;

        bool update(double deltaTime)
        {
            time_accumulator += deltaTime;

            // ¬ираховуЇмо тривал≥сть одного кадру
            double frame_duration = animation_duration / total_frames;
            bool finished_loop = false;

            if (time_accumulator >= frame_duration)
            {
                int framesToNext = static_cast<int>(time_accumulator / frame_duration);

                int next_frame = current_frame + framesToNext;
                if (next_frame >= total_frames)
                {
                    finished_loop = true; // јн≥мац≥€ д≥йшла до к≥нц€
                }

                current_frame = next_frame % total_frames;
                time_accumulator -= framesToNext * frame_duration;
            }

            return finished_loop;
        }

        void reset()
        {
            current_frame = 0;
            time_accumulator = 0.0;
        }
    };

    AnimationState state;
    SDL_Texture* texture = nullptr;
    float frame_width = 0.0f;
    float frame_height = 0.0f;
    float scale = 2.0f;
    float offset_x = 0.0f;
    float offset_y = 0.0f;

    void loadTexture(SDL_Renderer* renderer, std::string imagePath)
    {
        this->texture = IMG_LoadTexture(renderer, imagePath.c_str());
    }
};