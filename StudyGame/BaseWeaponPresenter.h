#pragma once
#include <SDL3/SDL_render.h>
#include "IWeaponPresenter.h"
#include "Rect.h"

class BaseWeaponPresenter : public IWeaponPresenter
{
private:
	Rect* hitBox;
	double* angle;

public:
	BaseWeaponPresenter(Rect* hitbox, double* angle) :
		hitBox(hitbox),
		angle(angle)
	{
	}

	~BaseWeaponPresenter() = default;

	void present(SDL_Renderer* renderer, const Weapon* weapon) override
	{
		SDL_FRect entityRect = toSDLFRect(*this->hitBox);
		Uint32 color = 10;
		
		SDL_FColor red = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		SDL_Texture* pixel = createWhitePixel(renderer);
		DrawRotatedRect(renderer, pixel, entityRect, *this->angle, red);
		SDL_DestroyTexture(pixel);
	}

	void DrawRotatedRect(SDL_Renderer* renderer, SDL_Texture* whitePixel,
		SDL_FRect rect, double angle, SDL_FColor color) {
		// 1. Встановлюємо колір (RGBA)
		SDL_SetTextureColorMod(
			whitePixel, (Uint8)(color.r * 255),
			(Uint8)(color.g * 255),
			(Uint8)(color.b * 255)
		);
		SDL_SetTextureAlphaMod(whitePixel, (Uint8)(color.a * 255));

		SDL_FPoint center = { 0, rect.h/2 };
		// 2. Малюємо як текстуру під кутом
		// NULL для srcRect означає використання всієї текстури (нашого одного пікселя)
		// NULL для center означає поворот навколо геометричного центру rect
		SDL_RenderTextureRotated(renderer, whitePixel, NULL, &rect, angle - 90, &center, SDL_FLIP_NONE);
	}

	SDL_Texture* createWhitePixel(SDL_Renderer* renderer)
	{
		SDL_Surface* surface = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA8888);
		SDL_FillSurfaceRect(surface, NULL, SDL_MapSurfaceRGBA(surface, 255, 255, 255, 255));

		// Створюємо текстуру з цієї поверхні
		SDL_Texture* pixelTexture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_DestroySurface(surface);

		return pixelTexture;
	}
};