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

	Vector2& operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vector2& operator*=(double koef)
	{
		this->x *= koef;
		this->y *= koef;

		return *this;
	}

	Vector2 operator*(double koef)
	{
		Vector2 res(*this); 
		res *= koef;     
		return res;
	}
};