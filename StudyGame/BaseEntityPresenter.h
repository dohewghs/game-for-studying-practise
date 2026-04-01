#pragma once
#include "IEntityPresenter.h"
#include "Entity.h"

class BaseEntityPresenter : public IEntityPresenter
{
public:
	void present(SDL_Renderer* renderer, const Entity* entity) override
	{
		SDL_FRect entityRect = toSDLFRect(entity->hitBox);
		Uint32 color = 10;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderRect(renderer, &entityRect);
	}
};