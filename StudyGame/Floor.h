#pragma once
#include "Rect.h"
#include <vector>
class Floor
{
private:
	std::vector<Rect> floor;

public:
	Floor();
	~Floor();

	bool hasIntersection(const Rect& rect) const;
	bool updateGroundCollision(Rect& rect) const;
};