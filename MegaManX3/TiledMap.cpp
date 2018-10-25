#include "TiledMap.h"

TiledMap::TiledMap()
{
}


TiledMap::~TiledMap()
{
}

void TiledMap::Init(string filePath)
{
	FILE* jsonFile = fopen(filePath.c_str(), "rb");
	if (jsonFile == NULL)
	{
		std::cout << "Error file";
	}

	fseek(jsonFile, 0, SEEK_END);
	long fileSize = ftell(jsonFile);
	rewind(jsonFile);

	char* json = new char[fileSize + 1];
	fread(json, 1, fileSize, jsonFile);
	json[fileSize] = '\0';

	Document document;
	document.Parse(json);

	const rapidjson::Value& layers = document["layers"];
	assert(layers.IsArray());
	const rapidjson::Value& tilesets = document["tilesets"];
	assert(tilesets.IsArray());

	assert(document["width"].IsNumber());
	assert(document["height"].IsNumber());
	assert(document["tilewidth"].IsNumber());
	assert(document["tileheight"].IsNumber());

	cols = document["width"].GetInt();
	rows = document["height"].GetInt();
	tileWidth = document["tilewidth"].GetInt();
	tileHeight = document["tileheight"].GetInt();

	string temp = tilesets[0]["image"].GetString();
	string bg_path = "Assets/" + temp;
	sprite = new GameSprite();
	sprite->Init(bg_path, D3DCOLOR_XRGB(255, 255, 255), cols * rows, rows, cols);
	sprite->SetScale(2, 2);

	const rapidjson::Value& bg_data = layers[0]["data"];

	data = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = bg_data[i * cols + j].GetInt();
		}
	}
}

void TiledMap::DrawMap()
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = 0; j < cols; j++)
		{
			float pos_x = ((float)(j * tileWidth) + (float)tileWidth / 2) * 2;
			float pos_y = ((float)((rows - i) * tileHeight) + (float)tileHeight / 2) * 2;
			if (pos_x >= rect_viewport->left - tileWidth && pos_x <= rect_viewport->right + tileWidth)
			{
				sprite->SetPosition(pos_x, pos_y);
				sprite->SetIndex(data[i][j]);
				sprite->Draw();
			}
		}
	}
}