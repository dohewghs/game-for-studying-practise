#pragma once

class Vector2
{
public:
	double x;
	double y;

	Vector2(double _x = 0, double _y = 0) :
		x(_x),
		y(_y)
	{
	};

	Vector2(const Vector2& other) :
		x(other.x),
		y(other.y)
	{
	};
};