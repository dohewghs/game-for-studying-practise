#pragma once
#include "ISpritePresenter.h"
#include "Entity.h"

class IEntityPresenter : public ISpritePresenter
{
protected:
	Entity const* entity;

public:
	IEntityPresenter(Entity* entity = nullptr)
	{
		this->entity = entity;
	}
	virtual ~IEntityPresenter() = default;

	virtual void present(SDL_Renderer* renderer) = 0;

	void setEntity(Entity* _entity)
	{
		this->entity = _entity;
	};
};