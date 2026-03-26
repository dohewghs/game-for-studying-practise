#pragma once
#include <SDL3/SDL_surface.h>
class IScene
{
public:
	virtual void present(SDL_Surface*& surface) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void handleInput() = 0;
};