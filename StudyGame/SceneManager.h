#pragma once
#include <vector>
#include "AppState.h"
#include "InputManager.h"

class IScene;

class SceneManager
{
private:
	IScene* currentScene;
	
	std::vector<IScene*> scenes;

public:
	SceneManager();

	~SceneManager();

	void changeScene(AppState state);

	IScene* getScene();

	void MakeScenes(InputManager* manager);
};