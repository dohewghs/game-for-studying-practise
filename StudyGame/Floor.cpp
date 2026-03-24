#include "Floor.h"

bool Floor::hasIntersection(const Rect& rect) const
{
	for (Rect floorRect : this->floor)
	{
		if (Rect::HasIntersection(floorRect, rect))
		{
			return true;
		}
	}
	return false;
}

bool Floor::updateGroundCollision(Rect& rect) const
{
	bool isNeedToZeroVelocity = false;

	for (Rect floorRect : this->floor)
	{
		if (Rect::HasIntersection(floorRect, rect))
		{
			double overlapY = (rect.y + rect.height) - floorRect.y;
			rect.y -= overlapY;
			
			isNeedToZeroVelocity = true;
			break;
		}
	}
	return isNeedToZeroVelocity;
}
