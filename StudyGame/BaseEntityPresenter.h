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

public:
	BaseEntityPresenter(Entity* entity)
	{
		this->entity = entity;
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

		SDL_RenderTexture(renderer, anim.texture, &srcRect, &dstRect);
	}

	void update(double deltaTime)
	{
		if (animations.find(currentAnimation) == animations.end())
			return;

		AnimationData& anim = animations[currentAnimation];

		anim.state.update(deltaTime);
	}
};