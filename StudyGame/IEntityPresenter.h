#pragma once
#include "ISpritePresenter.h"

class IEntityPresenter : public ISpritePresenter
{
protected:
	Entity const * entity;

public:
	virtual ~IEntityPresenter() = default;

	virtual void present(SDL_Renderer* renderer) = 0;
};