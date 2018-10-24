#pragma once
#include <string>
#include "GameSprite.h"
using namespace std;

class TiledMap
{
	int cols;
	int rows;
	int tiledWidth;
	int tiledHeight;
	int** data;
	GameSprite sprite;

	void InitSprite(string fileMapSprite);
public:
	TiledMap();
	~TiledMap();

	void Init(string fileMapMatrix, string fileMapSprite);
	void DrawMap();
};

