#pragma once
#include "Scene.h"
#include "GameSprite.h"
#include "Player.h"
#include "TiledMap.h"

class IntroScene :
	public Scene
{
private:
	GameSprite	background;
	Player		player;
	TiledMap	tiledmap;

public:

	IntroScene();
	~IntroScene();

	void Init();
	void Release();
	void Update(float dt);
	void Draw();
};

