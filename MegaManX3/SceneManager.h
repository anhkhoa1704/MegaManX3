#pragma once
#include "Scene.h"

class SceneManager
{
	Scene* current_scene;
public:

	void SetFirstScene(Scene* first_scene);
	void TranslateScene(Scene* translate_scene);
	void Update(float dt);
	void Draw();

	SceneManager();
	~SceneManager();
};


