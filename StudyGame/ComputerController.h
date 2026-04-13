#pragma once
#include "IController.h"

class ComputerController : public IController
{
public:
	~ComputerController() = default;

	Vector2 getInputDirection() override
	{
		return { 0,0 };
	}
	bool isJumpPressed() override
	{
		return false;
	}
	bool isAttack() override
	{
		return false;
	}
};