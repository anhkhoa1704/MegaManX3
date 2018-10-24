#include "TiledMap.h"
#include <fstream>
#include <iostream>
#include "Global.h"
using namespace std;

TiledMap::TiledMap()
{
}


TiledMap::~TiledMap()
{
}

void TiledMap::Init(string fileMapMatrix, string fileMapSprite)
{
	fstream fs;
	fs.open(fileMapMatrix.c_str(), ios::in);
	if (!fs)
		return;

	if (fs)
	{
		fs >> rows >> cols;
		fs >> tiledWidth >> tiledHeight;
	}

	data = new int*[rows];

	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols];
	}

	for (int i = rows - 1; i >= 0; i--)
	{
		if (fs)
		{
			for (int j = 0; j < cols; j++)
			{
				fs >> data[i][j];
			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}

	InitSprite(fileMapSprite);
}

void TiledMap::InitSprite(string fileMapSprite)
{
	D3DXIMAGE_INFO img_info;
	ZeroMemory(&img_info, sizeof(img_info));

	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileMapSprite.c_str(), &img_info);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Couldn't read image", "Message", MB_OK);
		return;
	}
	int rows_sprite = img_info.Height / tiledHeight;
	int cols_sprite = img_info.Width / tiledWidth;
	int total_frame = rows_sprite * cols_sprite;
	sprite.Init(fileMapSprite, D3DCOLOR_XRGB(0, 0, 0), total_frame, rows_sprite, cols_sprite);
	sprite.SetScale(2, 2);
}

void TiledMap::DrawMap()
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			float pos_x = ((float)j * tiledWidth + (float)tiledWidth / 2) * 2;
			float pos_y = ((float)i * tiledHeight + (float)tiledHeight / 2) * 2;
			if (pos_x >= rect_viewport->left - tiledWidth && pos_x <= rect_viewport->right + tiledWidth)
			{
				sprite.SetPosition(pos_x, pos_y);
				sprite.SetIndex(data[i][j]);
				sprite.Draw();
			}
		}
	}
}