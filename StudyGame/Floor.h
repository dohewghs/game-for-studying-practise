#pragma once
#include "Rect.h"
#include <vector>
#include <SDL3/SDL_render.h>

class IFloorPresenter;
class BaseFloorPresenter;

class Floor
{
private:
	std::vector<Rect> floor;
	IFloorPresenter* presenter;

public:
	Floor(IFloorPresenter* presenter);
	~Floor();

	bool hasIntersection(const Rect& rect) const;
	bool updateGroundCollision(Rect& rect) const;

	void present(SDL_Renderer*& renderer);
	friend class BaseFloorPresenter;
};