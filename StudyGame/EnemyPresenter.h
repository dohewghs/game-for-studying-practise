#pragma once
#include "BaseEntityPresenter.h"

class EnemyPresenter : public BaseEntityPresenter
{
public:
	EnemyPresenter(Entity* entity = nullptr) : BaseEntityPresenter(entity)
	{
	}

	~EnemyPresenter() = default;

	void present(SDL_Renderer* renderer) override
	{
		BaseEntityPresenter::present(renderer);

		SDL_FRect entityrect = toSDLFRect(entity->getHitBox());

		SDL_FRect dstRect;
		dstRect.x = entityrect.x;
		dstRect.y = entityrect.y;

		this->renderHealthBar(renderer, dstRect.x, dstRect.y-50, 2.0f);
	}

	void renderHealthBar(SDL_Renderer* renderer, float x, float y, float scale) 
	{
		SDL_Texture* atlas = ResourceManager::getTexture("health_atlas"); // завантажений 07.png

		const float spriteW = 16.0f; // Орієнтовно (144 / 8 стовпців)
		const float spriteH = 16.0f;

		const float rowY = 112;

		SDL_FRect srcRectBG = { 0.0f, rowY, spriteW, spriteH };

		SDL_FRect dstRect = { x, y, spriteW * scale + 20, spriteH * scale };

		SDL_RenderTexture(renderer, atlas, &srcRectBG, &dstRect);

		int fillIndex = this->healthIndex();

		if (fillIndex > 0) 
		{
			SDL_FRect srcRectFill = { (float)fillIndex * spriteW, rowY, spriteW, spriteH };

			SDL_RenderTexture(renderer, atlas, &srcRectFill, &dstRect);
		}
	}

	int healthIndex()
	{
		double percentage = this->entity->statistics.hp / this->entity->statistics.maxHp;

		// Індекс від 0 (порожньо) до 7 (повний)
		// У картинці 7 станів заповнення після рамки
		int frameIndex = (int)(percentage * 7);

		// Обмежуємо значення, щоб не вийти за межі
		if (frameIndex < 1) frameIndex = 0;
		if (frameIndex > 7) frameIndex = 7;

		return frameIndex;
	}
};