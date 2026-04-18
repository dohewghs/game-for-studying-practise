#pragma once
#include <SDL3/SDL_render.h>
#include "Entity.h"

class GameUI
{
public:
	void present(SDL_Renderer* renderer, const Entity* entity)
	{
		// малювати там здоровя, чи ще якусь інформацію про entity
	}
};