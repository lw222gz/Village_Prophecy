#pragma once
#include "IGameArea.h"

class HostileGameArea : public IGameArea
{
public:
	HostileGameArea(Vector2u size, TextureLoader *textures);
	~HostileGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<IGameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(IGameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	void RespawnEnemies(int daysLeft);

private:
	TextureLoader *textures;
	void generateGameArea();
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<IGameObject*> areaObjects;
	vector<Path*> areaPaths;

	Path *path = NULL;
	VisualEnemy *enemy = NULL;

	void SpawnEnemies(int amount);

	int maxAmountOfEnemies = 10;
	int enemyMinLevels = 1;
	int enemyMaxLevels = 3;	
};

