#pragma once
#include <SDL3/SDL_rect.h>

class Rect
{
public:
	double x;
	double y;
	double width;
	double height;

	Rect(double _x = 0, double _y = 0, double _width = 0, double _height = 0);

	Rect(const Rect& other);

	Rect& operator=(const Rect& other) = default;

	~Rect() = default;

	friend bool HasIntersection(const Rect& first, const Rect& second);
	friend SDL_Rect toSDLRect(const Rect& rect);
	friend SDL_FRect toSDLFRect(const Rect& rect);
};