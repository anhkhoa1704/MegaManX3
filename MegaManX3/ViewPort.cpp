#include "ViewPort.h"
#include "Global.h"

ViewPort* view_port = nullptr;

void ViewPort::CalculateViewPortPos(float x, float y)
{
	viewport_x = x - SCREEN_WIDTH / 2;
	if (viewport_x <= 0.0f)
		viewport_x = 0.0f;
	if (viewport_x >= 4096 - SCREEN_WIDTH)
		viewport_x = 4096 - SCREEN_WIDTH;
	viewport_y = SCREEN_HEIGHT;
	/*if (y >= 460)
		viewport_y = SCREEN_HEIGHT + 90;
	else if (y >= 240 && y < 460)
		viewport_y = SCREEN_HEIGHT - 120;*/
}

float ViewPort::GetViewPortX()
{
	return viewport_x;
}

float ViewPort::GetViewPortY()
{
	return viewport_y;
}

RECT* ViewPort::GetRectViewPort()
{
	RECT* rect = new RECT();
	rect->top = viewport_y;
	rect->left = viewport_x;
	rect->bottom = rect->top + SCREEN_HEIGHT;
	rect->right = rect->left + SCREEN_WIDTH;
	return rect;
}


ViewPort::ViewPort()
{
	view_port = this;
	viewport_x = 0.0f;
	viewport_y = 0.0f;
}

ViewPort::~ViewPort()
{
}
