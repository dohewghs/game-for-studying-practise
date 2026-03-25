#pragma once
#include "Rect.h"
#include <vector>

class IFloorPresenter;

class Floor
{
private:
	std::vector<Rect> floor;
	IFloorPresenter* presenter;

public:
	Floor(IFloorPresenter*& presenter);
	~Floor();

	bool hasIntersection(const Rect& rect) const;
	bool updateGroundCollision(Rect& rect) const;
};