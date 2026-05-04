#pragma once
#include <vector>
#include <string>
#include <SDL3/SDL_keyboard.h>
#include <fstream>

class InputManager
{
public:
	enum class direction
	{
		left,
		right,
		jump,
		attack,
		interaction
	};

private:
	std::vector<SDL_Scancode> keysBindings;

public:
	InputManager()
	{
		this->keysBindings = std::vector<SDL_Scancode>((int)direction::interaction+1);

		this->keysBindings[(int)direction::left] = SDL_SCANCODE_A;
		this->keysBindings[(int)direction::right] = SDL_SCANCODE_D;
		this->keysBindings[(int)direction::jump] = SDL_SCANCODE_SPACE;
		this->keysBindings[(int)direction::attack] = SDL_SCANCODE_BACKSPACE;
		this->keysBindings[(int)direction::interaction] = SDL_SCANCODE_E;

	}

	~InputManager() = default;

	SDL_Scancode getKey(direction dir)
	{
		return this->keysBindings[(int)dir];
	}

	void setKey(direction dir, SDL_Scancode keyCode)
	{
		this->keysBindings[(int)dir] = keyCode;
	}

	const char* getKeyName(direction dir)
	{
		return SDL_GetScancodeName(this->keysBindings[(int)dir]);
	}

	void saveToFile(const std::string& filename) 
	{
		std::ofstream ofs(filename, std::ios::binary);
		if (ofs.is_open()) 
		{
			size_t size = keysBindings.size();
			ofs.write(reinterpret_cast<const char*>(keysBindings.data()), size * sizeof(SDL_Scancode));
			ofs.close();
		}
	}

	void loadFromFile(const std::string& filename) 
	{
		std::ifstream ifs(filename, std::ios::binary);
		if (ifs.is_open()) 
		{
			ifs.read(reinterpret_cast<char*>(keysBindings.data()), keysBindings.size() * sizeof(SDL_Scancode));
			ifs.close();
		}
	}
};