#pragma once
#include "IGameArea.h"

class BaseGameArea : virtual public IGameArea
{
public:
	BaseGameArea(Vector2u size);
	~BaseGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<GameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(GameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	bool playerHasBurningFirePlace();

private:
	void generateGameArea();
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<GameObject*> areaObjects;
	vector<Path*> areaPaths;
};

