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
	sprite_run.Init("Assets/megaman-sprite/run-34x35.png", D3DCOLOR_XRGB(50, 96, 166), 12, 1, 12);
	sprite_jump.Init("Assets/megaman-sprite/jump-30x46.png", D3DCOLOR_XRGB(50, 96, 166), 10, 1, 10);
	sprite_dash.Init("Assets/megaman-sprite/dash-38x34.png", D3DCOLOR_XRGB(50, 96, 166), 3, 1, 3);
	sprite_stand.Init("Assets/megaman-sprite/dash-38x34.png", D3DCOLOR_XRGB(50, 96, 166), 3, 1, 3);
	sprite = sprite_dash;
	state = STAND;
	pos.x = sprite.frame_width;
	pos.y = 720 * 2 + sprite.frame_height;
	sprite.SetScale(2, 2);
	sprite.SetPosition(pos.x, pos.y);
	sprite.SetIndex(0);
	vx = 0;
	vy = 0;
}

void Player::Update(float dt)
{
	ProcessInput();

	pos.x += vx;
	pos.y += vy;

	if (pos.x <= sprite.frame_width)
		pos.x = sprite.frame_width;
	if (pos.x >= 4896 - sprite.frame_width)
		pos.x = 4896 - sprite.frame_width;
	
	sprite.SetScale(2, 2);
	if (vx < 0)
	{
		sprite.SetScale(-2, 2);
	}

	sprite.Update(dt);
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
	
	switch (state)
	{
	case STAND:
		if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_RIGHT))
		{
			vx = 10.0f;
			sprite.SetStartEnd(0, 2);
		}
		else if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_LEFT))
		{
			vx = -10.0f;
			sprite.SetStartEnd(0, 2);
		}
		else if (KeyBoard::GetKeyBoard()->IsKeyDown(DIK_SPACE))
		{
			vx = 0.0f;
			vy = 10.0f;
			state = JUMP;
			sprite = sprite_dash;
			sprite.SetStartEnd(0, 9);
		}
		else
		{
			vx = 0;
			sprite.SetStartEnd(0, 0);
		}
		break;
	case RUN:
		break;
	case JUMP:
		break;
	case DASH:
		break;
	default:
		break;
	}
	
}

