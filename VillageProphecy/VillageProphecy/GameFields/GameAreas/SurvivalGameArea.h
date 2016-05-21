#pragma once
#include "../../BaseClasses/IGameArea.h"

class SurvivalGameArea : public IGameArea
{
public:
	SurvivalGameArea(Vector2u size, TextureLoader *textures);
	~SurvivalGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<IGameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(IGameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	void RespawnResources(int amountOfDaysLeft);

private:
	void generateGameArea();
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<IGameObject*> areaObjects;
	vector<Path*> areaPaths;

	GameObject *gameObj = NULL;
	Path *path = NULL;
	TextureLoader *textures;

	struct Seed
	{
		int dayOfSprout = 0;
		int amountOfTrees = 0;
	};

	Seed seed;
	unsigned int maxAmountOfTrees = 10;
	void SpawnTrees(int amount);
	void PlantSeeds(int amountOfDaysLeft);
};

