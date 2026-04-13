#pragma once
#include <SDL3/SDL.h>
#include "IFloorPresenter.h"
#include "Floor.h"

class BaseFloorPresenter : public IFloorPresenter
{
	
public:
	~BaseFloorPresenter() = default;

	void present(SDL_Renderer*& renderer, const Floor* floor) override
	{
		for (const Rect& item : floor->floor)
		{
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

			SDL_FRect rect = toSDLFRect(item);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
};