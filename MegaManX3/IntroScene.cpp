#include "IntroScene.h"
#include "Global.h"

void IntroScene::Init()
{
	//background.Init("Assets/bg.jpg", D3DCOLOR_XRGB(0, 0, 0), 1, 1, 1);
	//background.SetScale(0.5, 0.5);
	//background.SetPosition((float) background.frame_width / 4, (float) background.frame_height / 4);
	tiledmap.Init("Assets/lv1.txt", "Assets/lv1.png");
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
	//background.Draw();
	tiledmap.DrawMap();
	player.Draw();
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
