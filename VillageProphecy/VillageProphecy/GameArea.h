#pragma once
//#include "Path.h"
//#include "GameAreas.h"
//#include "Direction.h"
//#include "Player.h"
#include "GameObject.h"
#include "VisualEnemy.h"
//#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GameArea
{
public:
	GameArea(Areas area, Vector2u size);
	~GameArea();
	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<GameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	Vector2u getAreaSize();
	void removeAreaObject(GameObject *obj);

	vector<VisualEnemy*>* getAreaEnemies();


private:
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<GameObject*> areaObjects;
	vector<Path*> areaPaths;
	void generateGameArea();
};

