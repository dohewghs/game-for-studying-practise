#pragma once
#include "IScene.h"

class MenuScene : public IScene
{

public:
	void present(SDL_Surface*& surface) override;
	void update(float deltaTime) override;
	void handleInput() override;
};