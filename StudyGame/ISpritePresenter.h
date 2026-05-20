#pragma once
#include "AnimationData.h"

#include <unordered_map>
#include <string>

class ISpritePresenter
{
private:
    std::unordered_map<std::string, AnimationData> animations;
    std::string currentAnimation;
    std::string nextAnimation;

    SDL_FlipMode flipMode = SDL_FLIP_NONE;
    Vector2 direction = { 0,0 };

    
protected:
    bool cancelUpdate = false;

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
    void addAnimation(SDL_Texture* texture, const std::string& name, int frames, float scale, float off_x, float off_y)
    {
        AnimationData anim;

        anim.texture = texture;

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
            SDL_Log("Помилка завантаження отут: %s", SDL_GetError());
        }
    }

    AnimationData& getCurrentAnimation()
    {
        return animations[currentAnimation];
    }
public:
    ISpritePresenter()
    {
        this->animations = std::unordered_map<std::string, AnimationData>();
        this->currentAnimation = "";
        this->nextAnimation = "";
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

        if (animations.find(name) == animations.end())
            return;

        if (currentAnimation == name || nextAnimation == name)
            return;

        if (name == "hurt")
        {
            this->animations[currentAnimation].state.reset();
            
            std::swap(this->currentAnimation, this->nextAnimation);
            
            this->currentAnimation = name;
        }

        nextAnimation = name;
    }

    void update(double deltaTime)
    {
        if (this->cancelUpdate)
            return;

        std::cout << this->currentAnimation << std::endl;

        this->updateFlipMode();

        bool loopFinished = this->animations[currentAnimation].state.update(deltaTime);

        if (loopFinished && !nextAnimation.empty())
        {
            currentAnimation = nextAnimation;
            nextAnimation = "";

            animations[currentAnimation].state.reset();
        }
    }

    void RenderCurrentTexture(SDL_Renderer* renderer, const SDL_FRect* srcRect, const SDL_FRect* dstRect)
    {
        if (animations.find(currentAnimation) == animations.end())
            return;

        auto anim = animations[currentAnimation];

        SDL_RenderTextureRotated(renderer, anim.texture, srcRect, dstRect, 0.0, NULL, this->flipMode);
    }

    void updateFlipMode()
    {
        if (this->direction.x < 0)
        {
            this->flipMode = SDL_FLIP_HORIZONTAL;
        }
        else
            this->flipMode = SDL_FLIP_NONE;
    }

    void setDirection(Vector2 dir)
    {
        this->direction = dir;
    }

    virtual void present(SDL_Renderer* renderer) = 0;
};