#pragma once

class Floor;

class IFloorPresenter
{
public:
	virtual void present(SDL_Surface*& surface, const Floor& floor) = 0;
};