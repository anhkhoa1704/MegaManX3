#include "GameObject.h"
#define SCALE 2

GameObject::GameObject(int id, int gid, float x, float y, float vx, float vy, int width, int height, GameSprite* sprite)
{
	this->id = id;
	this->gid = gid;
	this->pos.z = 0;
	this->vx = vx;
	this->vy = vy;
	this->width = width;
	this->height = height;
	this->sprite = sprite;
	this->pos.x = (x + width / 2)* SCALE;
	this->pos.y = (1536 - y + height / 2) * SCALE;
	sprite->SetPosition(pos.x, pos.y);
	sprite->SetScale(SCALE, SCALE);
}

void GameObject::SetPosition(D3DXVECTOR3 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

D3DXVECTOR3 GameObject::GetPosition()
{
	return pos;
}

void GameObject::Update(float dt)
{
	sprite->Update(dt);
}

void GameObject::Draw()
{
	sprite->Draw();
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
