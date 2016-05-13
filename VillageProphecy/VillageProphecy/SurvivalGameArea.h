#pragma once
#include "IGameArea.h"

class SurvivalGameArea : public IGameArea
{
public:
	SurvivalGameArea(Vector2u size);
	~SurvivalGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<GameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(GameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	void RespawnResources(int amountOfDaysLeft);

private:
	void generateGameArea(); 
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<GameObject*> areaObjects;
	vector<Path*> areaPaths;

	GameObject *gameObj = NULL;
	Path *path = NULL;

	struct Seed
	{
		int dayOfSprout = 0;
		int amountOfTrees = 0;
	};

	Seed seed;
	int maxAmountOfTrees = 10;
	void SpawnTrees(int amount);
	void GrowTrees(int amountOfDaysLeft);
};

