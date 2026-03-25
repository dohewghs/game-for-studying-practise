#pragma once
#include <SDL3/SDL.h>
#include "IFloorPresenter.h"
#include "Floor.h"

class BaseFloorPresenter : public IFloorPresenter
{
	
public:
	void present(SDL_Surface*& surface, const Floor& floor) override
	{
		Uint32 color = 0;
		for (auto item : floor.floor)
		{
			SDL_FillSurfaceRect(surface, &toSDLRect(item), color);
		}
	}
};