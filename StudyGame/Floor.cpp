#include "Floor.h"
#include "IFloorPresenter.h"

Floor::Floor(IFloorPresenter* _presenter)
{
	this->floor = std::vector<Rect>();
	floor.push_back(Rect(0, 200, 500, 10));

	this->presenter = _presenter;
}

Floor::~Floor() = default;

bool Floor::hasIntersection(const Rect& rect) const
{
	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			return true;
		}
	}
	return false;
}

bool Floor::updateGroundCollision(Rect& rect) const
{
	bool isNeedToZeroVelocity = false;

	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			double overlapY = (rect.y + rect.height) - floorRect.y;
			rect.y -= overlapY;
			
			isNeedToZeroVelocity = true;
			break;
		}
	}
	return isNeedToZeroVelocity;
}

void Floor::present(SDL_Renderer*& renderer)
{
	this->presenter->present(renderer, this);
}
