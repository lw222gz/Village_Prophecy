#pragma once
#include "IGameArea.h"

class HostileGameArea : public IGameArea
{
public:
	HostileGameArea(Vector2u size);
	~HostileGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<GameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(GameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	void RespawnEnemies(int daysLeft);

private:
	void generateGameArea();
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<GameObject*> areaObjects;
	vector<Path*> areaPaths;

	Path *path = NULL;
	VisualEnemy *enemy = NULL;

	void SpawnEnemies(int amount);

	int maxAmountOfEnemies = 10;
	int enemyMinLevels = 1;
	int enemyMaxLevels = 3;	
};

