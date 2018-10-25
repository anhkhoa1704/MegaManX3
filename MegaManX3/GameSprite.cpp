#include "GameSprite.h"
#include "Global.h"

GameSprite::GameSprite()
{
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	index = 0;
	start = 0;
	end	= 0;
	pos = { 0, 0, 0 };
	scale = { 1, 1 };
	angle = 0;
	duration = 0;
	frame_time = 1.0f / 60;
}

GameSprite::~GameSprite()
{
	if (sprite_handle)
	{
		sprite_handle->Release();
		sprite_handle = NULL;
	}
	if (tex)
	{
		tex->Release();
		tex = NULL;
	}
}

void GameSprite::Init(std::string image_path, D3DCOLOR color, int total_frame, int rows, int cols)
{
	D3DXIMAGE_INFO img_info;
	ZeroMemory(&img_info, sizeof(img_info));
	
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(image_path.c_str(), &img_info);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Couldn't read image", "Message", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFileEx(
		graphics_device->device, 
		image_path.c_str(), 
		img_info.Width, 
		img_info.Height, 
		D3DX_DEFAULT, 
		0, 
		D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		color, 
		NULL, 
		NULL, 
		&tex
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Couldn't create texture", "Message", MB_OK);
		return;
	}
	hr = D3DXCreateSprite(graphics_device->device, &sprite_handle);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Couldn't create sprite", "Message", MB_OK);
		return;
	}
	
	this->total_frame = total_frame;
	this->rows = rows;
	this->cols = cols;
	this->color = color;
	this->end = total_frame;
	this->start = 0;

	InitRects(img_info.Width, img_info.Height);
}

void GameSprite::SetPosition(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = 0;
}

float GameSprite::GetPositionX()
{
	return this->pos.x;
}

float GameSprite::GetPositionY()
{
	return this->pos.y;
}

void GameSprite::Draw()
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -view_port->GetViewPortX();
	mt._42 = view_port->GetViewPortY();
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &pos, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)(rect[index].right - rect[index].left) / 2, (float)(rect[index].bottom - rect[index].top) / 2, 0);

	D3DXVECTOR2 centerScaleAndRotate = D3DXVECTOR2(p.x, p.y);

	D3DXMATRIX matrixScalingRotate;

	D3DXMatrixTransformation2D(&matrixScalingRotate,
		&centerScaleAndRotate,
		0.0f,
		&scale,
		NULL,
		NULL, 0);

	sprite_handle->SetTransform(&matrixScalingRotate);

	sprite_handle->Begin(D3DXSPRITE_ALPHABLEND);
	sprite_handle->Draw(tex, &rect[index], &center, &p, 0xffffffff);
	sprite_handle->End();
}

void GameSprite::InitRects(int img_width, int img_height)
{
	this->frame_width = img_width / cols;
	this->frame_height = img_height / rows;
	rect = new RECT[total_frame];
	for (int i = 0; i < total_frame; i++)
	{
		int j = i % cols;
		int k = i / cols;
		rect[i].left = frame_width * j;
		rect[i].top = frame_height * k;
		rect[i].right = rect[i].left + frame_width;
		rect[i].bottom = rect[i].top + frame_height;
	}
}

void GameSprite::Update(float dt)
{
	duration += dt;
	if (duration > frame_time)
	{
		index += 1;
		if (index > end)
			index = start;
		duration = 0;
	}
}

void GameSprite::SetIndex(int index)
{
	this->index = index;
}

void GameSprite::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
}

void GameSprite::SetStartEnd(int start, int end)
{
	this->start = start;
	this->end = end;
}
