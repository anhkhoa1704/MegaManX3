#include "SceneManager.h"

SceneManager* scene_manager = nullptr;

void SceneManager::SetFirstScene(Scene* first_scene)
{
	this->current_scene = first_scene;
	current_scene->Init();
}

void SceneManager::TranslateScene(Scene* translate_scene)
{
	this->current_scene = translate_scene;
	current_scene->Init();
}

void SceneManager::Update(float dt)
{
	current_scene->Update(dt);
}

void SceneManager::Draw()
{
	current_scene->Draw();
}

SceneManager::SceneManager()
{
	scene_manager = this;
	current_scene = nullptr;
}

SceneManager::~SceneManager()
{
	if (current_scene)
	{
		current_scene->Release();
		current_scene = nullptr;
	}
}
