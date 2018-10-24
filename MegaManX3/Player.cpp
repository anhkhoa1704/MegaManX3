#include "Player.h"
#include "Global.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::Init()
{
	sprite.Init("Assets/caveman.bmp", D3DCOLOR_XRGB(255, 0, 255), 12, 2, 8);
	pos.x = 3600 + sprite.frame_width / 2;
	pos.y = 64;
	sprite.SetScale(1, 1);
	sprite.SetPosition(pos.x, pos.y);
	sprite.SetStartEnd(0, 7);
	vx = 0;
	vy = 0;
}

void Player::Update(float dt)
{
	ProcessInput();

	pos.x += vx;

	if (pos.x <= sprite.frame_width / 2)
		pos.x = sprite.frame_width / 2;
	if (pos.x >= 4096 - sprite.frame_width / 2)
		pos.x = 4096 - sprite.frame_width / 2;

	/*if (vy > 0)
	{
		if (pos.y >= 98 && pos.y <= 98 + 100)
		{
			pos.y += vy;
		}
		if (pos.y > 98 + 90)
		{
			vy = -vy;
		}
	}
	if (vy < 0)
	{
		if (pos.y <= 98)
		{
			vy = 0;
			pos.y = 98;
		}
		pos.y += vy;
	}*/

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (vx > 0)
		{
			sprite.SetScale(1, 1);
			sprite.Update();
		}
		if (vx < 0)
		{
			sprite.SetScale(-1, 1);
			sprite.Update();
		}
		last_time = now;
	}

	sprite.SetPosition(pos.x, pos.y);
}

void Player::Draw()
{
	sprite.Draw();
}

void Player::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
	sprite.SetPosition(x, y);
}

float Player::GetPositionX()
{
	return pos.x;
}

float Player::GetPositionY()
{
	return pos.y;
}

void Player::ProcessInput()
{
	KeyBoard::GetKeyBoard()->ProcessKeyBoard();
	/*if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_SPACE))
	{
		if (pos.y == 98)
		{
			sprite.SetStartEnd(8, 10);
			sprite.SetIndex(8);
			vy = 20.0f;
		}
	}*/
	/*else */
	if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_RIGHT))
	{
		vx = 2.0f;
		sprite.SetStartEnd(1, 7);
	}
	else if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_LEFT))
	{
		vx = -2.0f;
		sprite.SetStartEnd(1, 7);
	}
	else
	{
		vx = 0;
		sprite.SetIndex(0);
	}
}

