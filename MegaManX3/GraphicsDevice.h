#pragma once
#include <d3d9.h>

class GraphicsDevice {

	LPDIRECT3D9			direct3d;

public:

	LPDIRECT3DDEVICE9	device;
	

	GraphicsDevice();
	~GraphicsDevice();

	void				Init(HWND h_wnd, int width, int height);
	void				Clear(D3DCOLOR color);
	bool				Begin();
	void				End();
	void				Present();
};

