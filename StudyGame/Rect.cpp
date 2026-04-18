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

bool HasIntersection(const Rect& first, const Rect& second)
{
	bool xOverlap = (first.x < second.x + second.width) && 
		(first.x + first.width > second.x);

	bool yOverlap = (first.y < second.y + second.height) && 
		(first.y + first.height > second.y);

	return (xOverlap && yOverlap);
}

SDL_Rect toSDLRect(const Rect& rect)
{
	return SDL_Rect(rect.x, rect.y, rect.width, rect.height);
}

SDL_FRect toSDLFRect(const Rect& rect)
{
	return SDL_FRect(rect.x, rect.y, rect.width, rect.height);
}

//Rect& Rect::operator=(const Rect& other)
//{
//	this->x = other.x;
//	this->y = other.y;
//	this->width = other.width;
//	this->height = other.height;
//}