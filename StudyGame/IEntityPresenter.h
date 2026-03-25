#pragma once
#include <SDL3/SDL.h>

class IEntityPresenter
{
public:
	virtual void present(SDL_Surface*& surface, const Entity* entity) = 0;
};