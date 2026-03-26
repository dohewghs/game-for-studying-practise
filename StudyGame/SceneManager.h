#pragma once
//#include "IScene.h"
class IScene;

class SceneManager
{
private:
	IScene* scene;

public:
	SceneManager() : scene(nullptr) {};

	void changeScene(IScene* newScene)
	{
		this->scene = newScene;
	}

	void 
};