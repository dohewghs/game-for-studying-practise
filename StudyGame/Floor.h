#pragma once
#include "Block.h"
#include "Vector2.h"
#include <vector>
#include "string"
#include <SDL3/SDL_render.h>
#include "BaseBlockPresenter.h"

class IFloorPresenter;
class BaseFloorPresenter;

class Floor
{
private:
	std::vector<Block> floor;
	IBlockPresenter* blockPresenter;

	void LoadFrom(std::string path);
public:
	Floor();
	~Floor() = default;

	bool hasIntersection(const Rect& rect) const;
	bool CollisionsY(Rect& rect, double VelocityY) const;
	bool CollisionsX(Rect& rect, double VelocityX) const;

	void moveOn(Vector2 offset);

	void present(SDL_Renderer*& renderer);
	friend class BaseFloorPresenter;
};