#pragma once
#include "IEntityPresenter.h"

class EnemyPresenter : public IEntityPresenter
{
private:
	Vector2 direction;
	SDL_FlipMode flipMode;
	double healthPoit;
public:
	EnemyPresenter(Entity* entity = nullptr) : IEntityPresenter(entity)
	{
		this->direction = { 0, 0 };
		this->flipMode = SDL_FLIP_NONE;
		this->healthPoit = 0;

		this->addAnimation(ResourceManager::getTexture("hero_idle"), "idle", 10, 2, 0, -40);
		this->addAnimation(ResourceManager::getTexture("Character Run"), "run", 16, 2, 0, -40);
	}

	~EnemyPresenter() = default;

	void present(SDL_Renderer* renderer) override
	{
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

		SDL_RenderTextureRotated(renderer, anim.texture, &srcRect, &dstRect, 0.0, NULL, this->flipMode);

		dstRect = toSDLFRect(entity->hitBox);
		this->renderHealthBar(renderer, dstRect.x, dstRect.y-50, 2.0f);
	}

	void renderHealthBar(SDL_Renderer* renderer, float x, float y, float scale) 
	{
		SDL_Texture* atlas = ResourceManager::getTexture("health_atlas"); // завантажений 07.png

		const float spriteW = 18.0f; // Орієнтовно (144 / 8 стовпців)
		const float spriteH = 16.0f;

		const float rowY = 112;

		SDL_FRect srcRectBG = { 0.0f, rowY, spriteW, spriteH };

		SDL_FRect dstRect = { x, y, spriteW * scale + 20, spriteH * scale };

		SDL_RenderTexture(renderer, atlas, &srcRectBG, &dstRect);

		int fillIndex = this->healthIndex();

		if (fillIndex > 0) 
		{
			SDL_FRect srcRectFill = { (float)fillIndex * spriteW, rowY, spriteW, spriteH };

			SDL_RenderTexture(renderer, atlas, &srcRectBG, &dstRect);
		}
	}

	int healthIndex()
	{
		double percentage = this->entity->statistics.hp / this->entity->statistics.maxHp;

		// Індекс від 0 (порожньо) до 7 (повний)
		// У картинці 7 станів заповнення після рамки
		int frameIndex = (int)(percentage * 7);

		// Обмежуємо значення, щоб не вийти за межі
		if (frameIndex < 1) frameIndex = 1;
		if (frameIndex > 7) frameIndex = 7;

		return frameIndex;
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
		if (this->direction != dir)
			this->direction = dir;
	}

};