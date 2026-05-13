#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <sdl3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

class ResourceManager
{
private:
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> textures;

	static ResourceManager& get()
	{
		static ResourceManager object;
		return object;
	}

	ResourceManager() : renderer(nullptr) {}

public:
	static void init(SDL_Renderer* _renderer)
	{
		get().renderer = _renderer;
	}

	static bool loadTexture(const std::string& name, const std::string& path)
	{
		std::cout << "DEBUG: Calling loadTexture now" << std::endl;

		if (!get().renderer)
		{
			std::cerr << "ResourceManager: Renderer not initialized!" << std::endl;
			return false;
		}

		SDL_Texture* tex = IMG_LoadTexture(get().renderer, path.c_str());
		if (!tex) 
		{
			std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
			return false;
		}

		get().textures[name] = tex;
		return true;
	}

	static SDL_Texture* getTexture(const std::string& name) 
	{
		/*std::cout << "Looking for: [" << name << "]. Available keys:" << std::endl;
		for (auto const& [key, val] : get().textures) {
			std::cout << " - [" << key << "]" << std::endl;
		}*/

		auto it = get().textures.find(name);

		if (it != get().textures.end()) 
			return it->second;
			
		return nullptr;
	}

	static void clean() {
		for (auto& pair : get().textures) {
			SDL_DestroyTexture(pair.second);
		}
		get().textures.clear();
	}
};
