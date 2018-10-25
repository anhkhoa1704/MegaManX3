#pragma once
#include "GameSprite.h"
#include <d3dx9.h>

enum Player_State {
	STAND = 0,
	RUN,
	JUMP,
	DASH
};

class Player
{
	GameSprite			sprite;
	GameSprite			sprite_stand;
	GameSprite			sprite_run;
	GameSprite			sprite_jump;
	GameSprite			sprite_dash;
	D3DXVECTOR3			pos;
	float				vx;
	float				vy;
	DWORD				last_time;
	Player_State		state;

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

