#pragma once
#include "Path.h"
#include "GameAreas.h"
#include "Direction.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GameArea
{
public:
	GameArea(Areas area, Vector2u size);
	~GameArea();
	Areas getAreaType();
	vector<IDrawAble*> getAreaObjects();
	vector<Path*> getAreaPaths();
	Vector2u getAreaSize();

private:
	vector<IDrawAble*> areaObjects;
	Vector2u areaSize;
	Areas areaType;
	void generateGameArea();
	Vector2f entryPoint;

	vector<Path*> areaPaths;
};

