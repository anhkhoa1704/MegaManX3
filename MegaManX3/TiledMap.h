#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "GameSprite.h"
#include "Global.h"

#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
using namespace rapidjson;



class TiledMap
{
	int cols;
	int rows;
	int tileWidth;
	int tileHeight;
	int** data;
	GameSprite* sprite;

public:
	TiledMap();
	~TiledMap();

	void Init(string filePath);
	void DrawMap();
};

