#pragma once
#include "IController.h"
#include "InputManager.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>

class UserController : public IController
{
private:

public:
	UserController() = default;
	~UserController() = default;

	Vector2 getInputDirection() override
	{
		Vector2 res(0, 0);

		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		SDL_Scancode right = InputManager::getKey(InputManager::direction::right);
		SDL_Scancode left = InputManager::getKey(InputManager::direction::left);

		if (state[right]) 
			res.x += 1;

		if (state[left])
			res.x -= 1;

		return res;
	}

	bool isJumpPressed() override
	{
		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		SDL_Scancode jump = InputManager::getKey(InputManager::direction::jump);

		if (state[jump])
		{
			return true;
		}

		return false;
	}

	bool isAttack() override
	{
		int numkeys;
		const bool* state = SDL_GetKeyboardState(&numkeys);

		SDL_Scancode attack = InputManager::getKey(InputManager::direction::attack);

		if (state[attack])
		{
			return true;
		}

		return false;
	}
};