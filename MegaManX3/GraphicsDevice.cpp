#include "GraphicsDevice.h"
#include "Global.h"

GraphicsDevice* graphics_device = nullptr;

GraphicsDevice::GraphicsDevice()
{
	graphics_device = this;
	direct3d = 0;
	device = 0;
}

GraphicsDevice::~GraphicsDevice()
{
	if (!direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
	if (!device)
	{
		device->Release();
		device = NULL;
	}
}

void GraphicsDevice::Init(HWND h_wnd, int width, int height)
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferWidth = width;
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = h_wnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		h_wnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&device);
}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	device->Clear(0, 0, D3DCLEAR_TARGET, color, 1.0f, 0);
}

bool GraphicsDevice::Begin()
{
	if (device->BeginScene() == S_OK)
		return true;
	else
		return false;
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}
