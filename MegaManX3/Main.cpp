#include <Windows.h>
#include "CGame.h"
#include "Global.h"
#include "IntroScene.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	CGame* game = new CGame(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	game->GameInit();
	scene_manager->SetFirstScene(new IntroScene());
	game->GameRun();
	game->GameExit();
	return 0;
}
