#include "TiledMap.h"
#define SCALE 2

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
	const rapidjson::Value& tilesets = document["tilesets"];

	// get data
	cols = document["width"].GetInt();
	rows = document["height"].GetInt();
	tileWidth = document["tilewidth"].GetInt();
	tileHeight = document["tileheight"].GetInt();

	string temp = tilesets[0]["image"].GetString();
	string bg_path = "Assets/" + temp;
	sprite = new GameSprite();
	sprite->Init(bg_path, D3DCOLOR_XRGB(255, 255, 255), cols * rows, rows, cols);
	sprite->SetScale(SCALE, SCALE);

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

	// get animation object
	if (layers[1].IsObject())
	{
		if (layers[1].HasMember("name"))
		{
			string name = layers[1]["name"].GetString();
			if (name == "AnimationObject")
			{
				const rapidjson::Value& objects = layers[1]["objects"];
				for (SizeType i = 0; i < objects.Size(); i++)
				{
					int gid = objects[i]["gid"].GetInt();
					int id = objects[i]["id"].GetInt();
					int width = objects[i]["width"].GetInt();
					int height = objects[i]["height"].GetInt();
					float x = objects[i]["x"].GetFloat();
					float y = objects[i]["y"].GetFloat();
					string temppath = "";
					string imagepath = "";
					int tilecount = 0;
					GameSprite* sprite = new GameSprite();
					for (SizeType j = 0; j < tilesets.Size(); j++)
					{
						if (tilesets[j]["firstgid"].GetInt() == gid)
						{
							temppath = tilesets[j]["image"].GetString();
							imagepath = "Assets/" + temppath;
							tilecount = tilesets[j]["tilecount"].GetInt();
						}
					}
					sprite->Init(imagepath, D3DCOLOR_XRGB(255, 255, 255), tilecount, 1, tilecount);
					GameObject animationObject(id, gid, x, y, 0, 0, width, height, sprite);
					listAnimationObject.push_back(animationObject);
				}
			}
		}
	}

	// get overlay object
	if (layers[2].IsObject())
	{
		if (layers[2].HasMember("name"))
		{
			string name = layers[2]["name"].GetString();
			if (name == "OverlayObject")
			{
				const rapidjson::Value& objects = layers[2]["objects"];
				for (SizeType i = 0; i < objects.Size(); i++)
				{
					int gid = objects[i]["gid"].GetInt();
					int id = objects[i]["id"].GetInt();
					int width = objects[i]["width"].GetInt();
					int height = objects[i]["height"].GetInt();
					float x = objects[i]["x"].GetFloat();
					float y = objects[i]["y"].GetFloat();
					string temppath = "";
					string imagepath = "";
					int tilecount = 0;
					GameSprite* sprite = new GameSprite();
					for (SizeType j = 0; j < tilesets.Size(); j++)
					{
						if (tilesets[j]["firstgid"].GetInt() == gid)
						{
							temppath = tilesets[j]["image"].GetString();
							imagepath = "Assets/" + temppath;
							tilecount = tilesets[j]["tilecount"].GetInt();
						}
					}
					sprite->Init(imagepath, D3DCOLOR_XRGB(255, 255, 255), tilecount, 1, tilecount);
					GameObject overlayObject(id, gid, x, y, 0, 0, width, height, sprite);
					listOverlayObject.push_back(overlayObject);
				}
			}
		}
	}
	int a = 0;
}

void TiledMap::Update(float dt)
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	std::list<GameObject>::iterator it;
	for (it = listAnimationObject.begin(); it != listAnimationObject.end(); ++it)
	{
		it->Update(dt);
	}
}

void TiledMap::DrawMap()
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	for (int i = rows - 1; i >= 0; i--)
	{
		for (int j = 0; j < cols; j++)
		{
			float pos_x = ((float)(j * tileWidth) + (float)tileWidth / 2) * SCALE;
			float pos_y = ((float)((rows - i) * tileHeight) - (float)tileHeight / 2) * SCALE;
			if (pos_x >= rect_viewport->left - (float)tileWidth / 2 * SCALE && pos_x <= rect_viewport->right + (float)tileHeight / 2 * SCALE)
			{
				sprite->SetPosition(pos_x, pos_y);
				sprite->SetIndex(data[i][j] - 1);
				sprite->Draw();
			}
		}
	}
}

void TiledMap::DrawAnimationObject()
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	std::list<GameObject>::iterator it;
	for (it = listAnimationObject.begin(); it != listAnimationObject.end(); ++it)
	{
		float pos_x = it->GetPosition().x;
		float pos_y = it->GetPosition().y;
		if (pos_x >= rect_viewport->left - (float)tileWidth / 2 * SCALE && pos_x <= rect_viewport->right + (float)tileHeight / 2 * SCALE)
		{
			it->Draw();
		}
	}
}

void TiledMap::DrawOverlayObject()
{
	RECT* rect_viewport = view_port->GetRectViewPort();
	std::list<GameObject>::iterator it;
	for (it = listOverlayObject.begin(); it != listOverlayObject.end(); ++it)
	{
		float pos_x = it->GetPosition().x;
		float pos_y = it->GetPosition().y;
		if (pos_x >= rect_viewport->left && pos_x <= rect_viewport->right)
		{
			it->Draw();
		}
	}
}