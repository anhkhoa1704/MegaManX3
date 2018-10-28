#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

#include "GameSprite.h"
#include "Global.h"
#include "GameObject.h"

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
	list<GameObject> listAnimationObject;
	list<GameObject> listOverlayObject;

public:
	TiledMap();
	~TiledMap();

	void Init(string filePath);
	void Update(float dt);
	void DrawMap();
	void DrawAnimationObject();
	void DrawOverlayObject();
};

