#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>

struct AnimationData
{
    struct AnimationState
    {
        int total_frames = 1;
        double animation_duration = 0.5;

        int current_frame = 0;
        double time_accumulator = 0.0;

        void update(double deltaTime)
        {
            time_accumulator += deltaTime;

            if (time_accumulator >= animation_duration)
            {
                int framesToNext = static_cast<int>(time_accumulator / animation_duration);

                current_frame = (current_frame + framesToNext) % total_frames;

                time_accumulator -= framesToNext * animation_duration;
            }
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

class ISpritePresenter
{
protected:
    std::unordered_map<std::string, AnimationData> animations;
    std::string currentAnimation;

    void addAnimation(SDL_Renderer* renderer, const std::string& name, const std::string& path,
        int frames, float scale, float off_x, float off_y)
    {
        AnimationData anim;
        anim.texture = IMG_LoadTexture(renderer, path.c_str());

        if (anim.texture)
        {
            float tex_w, tex_h;
            SDL_GetTextureSize(anim.texture, &tex_w, &tex_h);
            anim.frame_width = tex_w / frames;
            anim.frame_height = tex_h;
            anim.state.total_frames = frames;
            anim.scale = scale;
            anim.offset_x = off_x;
            anim.offset_y = off_y;

            this->animations[name] = anim;
        }
        else
        {
            SDL_Log("Помилка завантаження: %s", SDL_GetError());
        }
    }
public:
    ISpritePresenter()
    {
        this->animations = std::unordered_map<std::string, AnimationData>();
        this->currentAnimation = "";
    }
    virtual ~ISpritePresenter()
    {
        for (auto& pair : this->animations)
        {
            if (pair.second.texture) 
            {
                SDL_DestroyTexture(pair.second.texture);
            }
        }
    }

    void setAnimation(const std::string& name)
    {
        if (animations.find(name) != animations.end())
        {
            currentAnimation = name;
        }
    }

    virtual void present(SDL_Renderer* renderer) = 0;
    virtual void update(double deltaTime) = 0;
    virtual void setDirection(Vector2 dir) = 0;
};