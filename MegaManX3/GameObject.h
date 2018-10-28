#pragma once
#include <d3dx9.h>
#include "GameSprite.h"
#include <string>

class GameObject
{
private:
	D3DXVECTOR3		pos;
	float			vx;
	float			vy;
	int				width;
	int				height;
	GameSprite*		sprite;
	int				gid;
	int				id;

public:
	
	GameObject(int id, int gid, float x, float y, float vx, float vy, int width, int height, GameSprite* sprite);
	GameObject();
	~GameObject();

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition();
	void Update(float dt);
	void Draw();
};
