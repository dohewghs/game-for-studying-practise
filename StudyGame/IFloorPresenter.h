#pragma once

class Floor;

class IFloorPresenter
{
public:
	virtual ~IFloorPresenter() = default;

	virtual void present(SDL_Renderer*& renderer, const Floor* floor) = 0;
};