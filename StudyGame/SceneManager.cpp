#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include <iostream>

SceneManager::SceneManager() :
	currentScene(nullptr),
	scenes()
{
}

SceneManager::~SceneManager()
{
	for (IScene* scene : scenes) 
	{
		if (scene != nullptr) 
		{
			delete scene;
		}
	}

	this->currentScene = nullptr;
}

void SceneManager::changeScene(AppState state)
{
	int sceneIndex = static_cast<int>(state);

	if (this->currentScene == scenes[sceneIndex])
		return;

	if (!scenes[sceneIndex])
		return;

	currentScene = scenes[sceneIndex];
	currentScene->setState(state);
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
	this->scenes[static_cast<int>(AppState::game)] = new GameScene();
	this->scenes[static_cast<int>(AppState::settings)] = new SettingsScene();


	this->currentScene = this->scenes[static_cast<int>(AppState::menu)];
}
