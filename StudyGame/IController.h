#pragma once
class Vector2;

class IController
{
public:
	virtual ~IController() = default;

	virtual Vector2 getInputDirection() = 0;
};