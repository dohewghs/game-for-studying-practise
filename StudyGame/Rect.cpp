#include "Rect.h"

Rect::Rect(double _x, double _y, double _width, double _height) :
	x(_x),
	y(_y),
	width(_width),
	height(_height)
{
}

Rect::Rect(const Rect& other) :
	x(other.x),
	y(other.y),
	width(other.width),
	height(other.height)
{
}

bool Rect::HasIntersection(const Rect& first, const Rect& second)
{
	bool xOverlap = (first.x < second.x + second.width) && 
		(first.x + first.width > second.x);

	bool yOverlap = (first.y < second.y + second.height) && 
		(first.y + first.height > second.y);

	return (xOverlap && yOverlap);
}
