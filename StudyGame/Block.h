#pragma once
#include "Rect.h"
#include <iostream>

class Block : public Rect
{
	friend std::iostream& operator>>(std::iostream& is, Block& block)
	{
		is >> block.x >> block.y >> block.width >> block.height;

		char type;
		is >> type;
		switch (type)
		{
		case 'g':
			block.type = Block::grass;
			break;
		case 'd':
			block.type = Block::dirt;
			break;
		default:
			break;
		}

		return is;
	}
public:
	enum BlockType
	{
		grass,
		dirt
	};

	Block() : Rect()
	{
		this->type = grass;
	}
	
	BlockType getType() const { return this->type; }
	SDL_FRect getRect() const 
	{
		Rect rect = { this->x, this->y, this->width, this->height };
		return toSDLFRect(rect);
	}
private:
	BlockType type;
};