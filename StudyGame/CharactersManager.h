#pragma once
#include "Character.h"
#include <vector>
#include "UserController.h"
#include "BaseEntityPresenter.h"

class CharactersManager
{
private:
	std::vector<Character> characters;

public:
	CharactersManager()
	{
		this->characters = std::vector<Character>(10);
		characters[0] = Character(new Entity(), new UserController(), new BaseEntityPresenter());
	}

	~CharactersManager() = default;


	std::vector<Entity*> entities()
	{
		std::vector<Entity*> res = std::vector<Entity*>();

		for (Character& character : this->characters)
		{
			Entity* entity = character.getEntity();

			if (entity)
				res.push_back(entity);
		}

		return res;
	}

	void present(SDL_Renderer* renderer)
	{
		for (Character& character : this->characters)
		{
			character.present(renderer);
		}
	}
};
