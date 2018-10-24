#pragma once
#include <d3dx9.h>
#include <string>
#include "GraphicsDevice.h"

class GameSprite {

	LPDIRECT3DTEXTURE9	tex;
	D3DCOLOR			color;
	int					angle;
	D3DXVECTOR2			scale;
	
	RECT*				rect;			//list frame of image
	int					total_frame;
	int					rows;
	int					cols;
	int					index;			//current frame
	int					start;			//start of animation
	int					end;			//end of animation
	D3DXVECTOR3			pos;


	void				InitRects(int img_width, int img_height);

public:

	LPD3DXSPRITE		sprite_handle;
	int					frame_width;
	int					frame_height;
	

	GameSprite();
	~GameSprite();

	void				Init(std::string image_path, D3DCOLOR color, int total_frame, int rows, int cols);
	void				SetPosition(float x, float y);
	float				GetPositionX();
	float				GetPositionY();
	void				Draw();
	void				Update();
	void				SetIndex(int index);
	void				SetScale(float x, float y);
	void				SetStartEnd(int start, int end);
};