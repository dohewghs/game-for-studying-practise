#include "Floor.h"
#include "IFloorPresenter.h"

Floor::Floor(IFloorPresenter* _presenter)
{
	this->floor = std::vector<Rect>();
	floor.push_back(Rect(0, 400, 500, 10));
	floor.push_back(Rect(300, 300, 10, 100));

	this->presenter = _presenter;
}

Floor::~Floor()
{
	if (this->presenter)
		delete this->presenter;
}

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

bool Floor::CollisionsY(Rect& rect, double VelocityY) const
{
	bool isNeedToZeroVelocity = false;

	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			if (VelocityY > 0)
			{
				rect.y = floorRect.y - rect.height;
			}
			// If moving up, snap to bottom of floor
			else if (VelocityY < 0)
			{
				rect.y = floorRect.y + rect.height;
			}
			
			isNeedToZeroVelocity = true;
			break;
		}
	}
	return isNeedToZeroVelocity;
}

bool Floor::CollisionsX(Rect& rect, double VelocityX) const
{
	bool isNeedToZeroVelocity = false;

	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			if (VelocityX > 0)
			{
				rect.x = floorRect.x - rect.width;
			}
			else if (VelocityX < 0)
			{
				rect.x = floorRect.x + floorRect.width;
			}

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
