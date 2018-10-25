#pragma once
#include "GameSprite.h"

class Game
{

	int					width;
	int					height;
	bool				is_full_screen;

	HINSTANCE			h_instance;
	HWND				h_wnd;
	POINT				pos;

	static LRESULT CALLBACK WndProceduce(HWND h_wnd, UINT message, WPARAM wParam, LPARAM lParam);
	void				Draw();
	void				Update(float dt);

public:

	Game(HINSTANCE hInstance, int width, int height, bool is_full_screen);
	~Game();

	bool				InitWindow();
	void				GameInit();
	void				GameRun();
	void				GameExit();

};

