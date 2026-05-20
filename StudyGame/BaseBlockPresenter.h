#pragma once
#include <SDL3/SDL.h>
#include "IBlockPresenter.h"
#include "Block.h"
#include "ResourceManager.h"
#include <unordered_map>

class BaseBlockPresenter : public IBlockPresenter
{
private:
	std::unordered_map<char, SDL_Texture*> textures;
	const SDL_FRect srcGrass = { 0,0,16,16 };
	const SDL_FRect srcDirt = { 0,16,16,16 };
public:
	BaseBlockPresenter()
	{
		this->textures['g'] = ResourceManager::getTexture("world_tileset");
	}
	~BaseBlockPresenter() = default;

	void present(SDL_Renderer*& renderer, const Block& block) override
	{
		SDL_FRect dstrect = block.getRect();
		SDL_FRect srcrect;
		char type = 'g';

		switch (block.getType())
		{
		case Block::grass:
			srcrect = srcGrass;
			
			break;
		case Block::dirt:
			srcrect = srcDirt;
			type = 'g';
			break;
		default:
			srcrect = srcGrass;
			type = 'g';
			break;
		}

		SDL_RenderTexture(renderer, textures[type], &srcrect, &dstrect);
	}

	
};


struct Grass
{
	
};