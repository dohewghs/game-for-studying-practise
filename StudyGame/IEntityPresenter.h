#pragma once
#include <SDL3/SDL_render.h>

class IEntityPresenter
{
public:
	virtual void present(SDL_Renderer* renderer, const Entity* entity) = 0;
};