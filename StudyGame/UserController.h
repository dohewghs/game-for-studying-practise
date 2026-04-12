#pragma once
#include "IController.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>

class UserController : public IController
{
public:
	Vector2 getInputDirection() override
	{
		Vector2 res(0, 0);

		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		if (state[SDL_SCANCODE_D])
		{
			res.x = 1;
		}

		if (state[SDL_SCANCODE_A])
		{
			res.x = -1;
		}

		return res;
	}

	bool isJumpPressed() override
	{
		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		if (state[SDL_SCANCODE_SPACE])
		{
			return true;
		}

		return false;
	}

	bool isAttack() override
	{
		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		if (state[SDL_SCANCODE_BACKSPACE])
		{
			return true;
		}

		return false;
	}
};