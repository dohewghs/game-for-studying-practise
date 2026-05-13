#pragma once
#include "IEntityPresenter.h"
#include "Entity.h"

class BaseEntityPresenter : public IEntityPresenter
{
	bool isLoaded = false;
	void LoadAnimations(SDL_Renderer* renderer)
	{
		this->addAnimation(
			renderer,
			"idle",
			"..//..//..//..//assets//FREE_Samurai_2D//Sprites//IDLE.png",
			10,
			2,
			0,
			-40
		);

		this->addAnimation(
			renderer,
			"attack",
			"..//..//..//..//assets//FREE_Samurai_2D//Sprites//ATTACK.png",
			7,
			2,
			0,
			-40
		);

		this->addAnimation(
			renderer,
			"hurt",
			"..//..//..//..//assets//FREE_Samurai_2D//Sprites//HURT.png",
			4,
			2,
			0,
			-40
		);

		this->addAnimation(
			renderer,
			"run",
			"..//..//..//..//assets//FREE_Samurai_2D//Sprites//RUN.png",
			16,
			2,
			0,
			-40
		);
	}

	Vector2 direction;
	SDL_FlipMode flipMode;

public:
	BaseEntityPresenter(Entity* entity)
	{
		this->entity = entity;
		this->direction = { 0,0 };
	}

	~BaseEntityPresenter()
	{
		this->entity = nullptr;
	}

	void present(SDL_Renderer* renderer) override
	{
		if (!isLoaded)
		{
			this->LoadAnimations(renderer);
			this->setAnimation("idle");
			isLoaded = true;
		}

		const AnimationData& anim = animations[currentAnimation];

		if (!anim.texture)
			return;

		SDL_FRect srcRect =
		{
			anim.state.current_frame * anim.frame_width, 0.0f,
			anim.frame_width, anim.frame_height
		};

		SDL_FRect dstRect = toSDLFRect(entity->hitBox);
		float center_x = dstRect.x + (dstRect.w / 2.0f);
		float center_y = dstRect.y + (dstRect.h / 2.0f);

		dstRect.w = anim.frame_width * anim.scale;
		dstRect.h = anim.frame_height * anim.scale;
		dstRect.x = center_x - (dstRect.w / 2.0f) + anim.offset_x;
		dstRect.y = center_y - (dstRect.h / 2.0f) + anim.offset_y;

		//SDL_RenderTexture(renderer, anim.texture, &srcRect, &dstRect);
		SDL_RenderTextureRotated(renderer, anim.texture, &srcRect, &dstRect, 0.0, NULL, this->flipMode);
	}

	void update(double deltaTime) override
	{
		if (animations.find(currentAnimation) == animations.end())
			return;

		AnimationData& anim = animations[currentAnimation];

		anim.state.update(deltaTime);

		if (this->direction.x < 0)
			this->flipMode = SDL_FLIP_HORIZONTAL;
		else
			this->flipMode = SDL_FLIP_NONE;
	}

	void setDirection(Vector2 dir) override
	{
		this->direction = dir;
	}
};