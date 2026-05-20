#pragma once

class Block;

class IBlockPresenter
{
public:
	virtual ~IBlockPresenter() = default;

	virtual void present(SDL_Renderer*& renderer, const Block& floor) = 0;
};