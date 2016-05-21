#pragma once
#include "../../BaseClasses/IGameArea.h"
#include "../../GameObjects/GameObject_FirePlace.h"
#include "../../GameObjects/GameObject_Bed.h"

class BaseGameArea : public IGameArea
{
public:
	BaseGameArea(Vector2u size, TextureLoader *textures);
	~BaseGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<IGameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(IGameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);

	bool playerHasBurningFirePlace();
	void firePlaceBurnOut();




private:
	void generateGameArea();
	vector<VisualEnemy*> enemies;
	vector<IDrawAble*> areaVisualObjects;
	Vector2u areaSize;
	Areas areaType;
	Vector2f entryPoint;
	vector<IGameObject*> areaObjects;
	vector<Path*> areaPaths;

	TextureLoader *textures;

	GameObject_FirePlace *firePlace = NULL;
};

