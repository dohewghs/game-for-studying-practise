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
	bool CollisionsY(Rect& rect, double VelocityY) const;
	bool CollisionsX(Rect& rect, double VelocityX) const;


	void present(SDL_Renderer*& renderer);
	friend class BaseFloorPresenter;
};