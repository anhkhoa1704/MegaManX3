#pragma once
#include "GameSprite.h"
#include <d3dx9.h>

class Player
{
	GameSprite			sprite;
	D3DXVECTOR3			pos;
	float				vx;
	float				vy;
	DWORD				last_time;

public:

	Player();
	~Player();

	void				Init();
	void				Update(float dt);
	void				Draw();
	void				SetPosition(int x, int y);
	float				GetPositionX();
	float				GetPositionY();
	void				ProcessInput();
};

