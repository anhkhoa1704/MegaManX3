#pragma once
#include <d3dx9.h>
class ViewPort
{
	float	viewport_x;
	float	viewport_y;

public:

	void	CalculateViewPortPos(float x, float y);
	float	GetViewPortX();
	float	GetViewPortY();
	RECT*	GetRectViewPort();

	ViewPort();
	~ViewPort();
};

