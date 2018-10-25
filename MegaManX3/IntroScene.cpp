#include "IntroScene.h"
#include "Global.h"

void IntroScene::Init()
{
	tiledmap.Init("Assets/example.json");
	player.Init();
}

void IntroScene::Release()
{
}

void IntroScene::Update(float dt)
{
	player.Update(dt);
	view_port->CalculateViewPortPos(player.GetPositionX(), player.GetPositionY());
}

void IntroScene::Draw()
{
	tiledmap.DrawMap();
	player.Draw();
	
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
