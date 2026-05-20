#include "Floor.h"
#include <fstream>
#include <sstream>

Floor::Floor()
{
	this->floor = std::vector<Block>();
	this->blockPresenter = new BaseBlockPresenter();

	this->LoadFrom("..//..//..//..//assets//Maps//map1.txt");
}

void Floor::LoadFrom(std::string path)
{
	std::ifstream inFile(path);

	std::string line;

	while (std::getline(inFile, line))
	{
		std::stringstream ss(line);
		
		Block block;

		ss >> block;
		
		this->floor.push_back(block);
	}
}

bool Floor::hasIntersection(const Rect& rect) const
{
	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			return true;
		}
	}
	return false;
}

bool Floor::CollisionsY(Rect& rect, double VelocityY) const
{
	bool isNeedToZeroVelocity = false;

	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			if (VelocityY > 0)
			{
				rect.y = floorRect.y - rect.height;
			}
			// If moving up, snap to bottom of floor

			
			else if (VelocityY < 0)
			{
				rect.y = floorRect.y + rect.height;
			}
			
			isNeedToZeroVelocity = true;
			break;
		}
	}
	return isNeedToZeroVelocity;
}

bool Floor::CollisionsX(Rect& rect, double VelocityX) const
{
	bool isNeedToZeroVelocity = false;

	for (const Rect& floorRect : this->floor)
	{
		if (HasIntersection(floorRect, rect))
		{
			if (VelocityX > 0)
			{
				rect.x = floorRect.x - rect.width;
			}
			else if (VelocityX < 0)
			{
				rect.x = floorRect.x + floorRect.width;
			}

			isNeedToZeroVelocity = true;
			break;
		}
	}
	return isNeedToZeroVelocity;
}

void Floor::present(SDL_Renderer*& renderer)
{
	for (const Block& block : this->floor)
	{
		this->blockPresenter->present(renderer, block);
	}
}

void Floor::moveOn(Vector2 offset)
{
	for (Rect& rect : this->floor)
	{
		rect.x += offset.x;
		rect.y += offset.y;
	}
}