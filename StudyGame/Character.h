#pragma once
#include "Entity.h"

class Character
{
private:
	Entity* entity = nullptr;
	IController* controller = nullptr;

public:
	Character(Entity* _entity = nullptr, IController* _controller = nullptr);
	Character(const Character& other) = delete;
	Character(Character&& other) noexcept;
	~Character();

	Character& operator=(Character&& other) noexcept;
	operator bool() const;

	void present(SDL_Renderer* renderer);
	void applyAcceleration(double deltaTime);
	void handleInput();

	Entity* getEntity();
};