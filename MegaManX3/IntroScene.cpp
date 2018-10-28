#include "IntroScene.h"
#include "Global.h"
#define SCALE 0.25

void IntroScene::Init()
{
	tiledmap.Init("Assets/IntroStage-tile-map.json");
	player.Init();
}

void IntroScene::Release()
{
}

void IntroScene::Update(float dt)
{
	tiledmap.Update(dt);
	player.Update(dt);
	view_port->CalculateViewPortPos(player.GetPositionX(), player.GetPositionY());
}

void IntroScene::Draw()
{
	tiledmap.DrawMap();
	tiledmap.DrawAnimationObject();
	player.Draw();
	tiledmap.DrawOverlayObject();
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
