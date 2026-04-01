#include "SceneManager.h"

SceneManager::SceneManager() :
	currentScene(nullptr),
	scenes()
{
}

SceneManager::~SceneManager()
{
	this->currentScene = nullptr;

	for (IScene* scene : scenes)
	{
		delete scene;
	}
}

void SceneManager::changeScene(AppState state)
{
	int sceneIndex = static_cast<int>(state);

	if (this->currentScene == scenes[sceneIndex])
		return;

	if (!scenes[sceneIndex])
		return;

	currentScene = scenes[sceneIndex];
}

IScene* SceneManager::getScene()
{
	if (currentScene == nullptr)
		throw std::exception("current scene nullptr");

	return this->currentScene;
}

void SceneManager::MakeScenes()
{
	this->scenes.resize(10);

	this->scenes[static_cast<int>(AppState::menu)] = new MenuScene();

	this->currentScene = this->scenes[static_cast<int>(AppState::menu)];
}
