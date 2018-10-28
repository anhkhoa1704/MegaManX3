#include "Game.h"
#include "Global.h"

Game::Game(HINSTANCE hInstance, int width, int height, bool is_full_screen)
{
	this->h_instance = hInstance;
	this->h_wnd = 0;
	this->is_full_screen = is_full_screen;
	if (is_full_screen)
	{
		this->width = 1366;
		this->height = 768;
		this->pos = { 0, 0 };
	}
	else
	{
		this->width = width;
		this->height = height;
		this->pos = { 50, 50 };
	}
}

bool Game::InitWindow()
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbSize = sizeof(WNDCLASSEX);
	WndcEx.hInstance = this->h_instance;
	WndcEx.lpfnWndProc = (WNDPROC) WndProceduce;
	WndcEx.lpszClassName = "Game";
	if (!RegisterClassEx(&WndcEx))
	{
		return false;
	}
	DWORD window_style;
	if (is_full_screen)
	{
		window_style = WS_EX_TOPMOST | WS_POPUP;
	}
	else
	{
		window_style = WS_EX_TOPMOST | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	}
	this->h_wnd = CreateWindow(
		"Game",
		"Castle Vania",
		window_style,
		pos.x,
		pos.y,
		this->width,
		this->height,
		0,
		0,
		this->h_instance,
		0
	);
	if (!h_wnd)
	{
		return false;
	}
	ShowWindow(h_wnd, SW_SHOW);
	UpdateWindow(h_wnd);
	return true;
}

void Game::GameInit()
{
	InitWindow();
	new SceneManager();
	new GraphicsDevice();
	new ViewPort();
	KeyBoard::GetKeyBoard()->InitKeyboard(h_wnd);
	graphics_device->Init(h_wnd, width, height);
}

void Game::GameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	int done = 0;
	
	UINT frame_time = 1000 / FPS;
	UINT delta_time = frame_time;
	UINT start_time = 0;

	while (!done)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		UINT now = GetTickCount();
		delta_time = now - start_time;
		
		if (delta_time >= frame_time)
		{
			Update(delta_time);
			start_time = now;
			Draw();
		}

	}
}

void Game::Update(float dt)
{
	scene_manager->Update(dt);
}

void Game::Draw()
{
	graphics_device->Clear(D3DCOLOR_XRGB(51, 51, 51));

	if (graphics_device->Begin())
	{
		scene_manager->Draw();

		graphics_device->End();
	}
	graphics_device->Present();
}

void Game::GameExit()
{
	graphics_device->~GraphicsDevice();
}

LRESULT CALLBACK Game::WndProceduce(HWND h_wnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(h_wnd, message, wParam, lParam);
}

Game::~Game()
{
}

