#pragma once
#include "IEntityPresenter.h"
#include "Entity.h"

class BaseEntityPresenter : public IEntityPresenter
{
public:
	void present(SDL_Surface*& surface, const Entity* entity) override
	{
		SDL_Rect entityRect = toSDLRect(entity->getHitBox());
		Uint32 color = 10;

		SDL_FillSurfaceRect(surface, &entityRect, color);
	}
};