#pragma once
#include "IGameArea.h"

class FinalGameArea : public IGameArea
{
public:
	FinalGameArea(Vector2u size);
	~FinalGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<GameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(GameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

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

