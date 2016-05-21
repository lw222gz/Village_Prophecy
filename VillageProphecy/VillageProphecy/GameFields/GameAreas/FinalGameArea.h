#pragma once
#include "../../BaseClasses/IGameArea.h"

class FinalGameArea : public IGameArea
{
public:
	FinalGameArea(Vector2u size, TextureLoader *textures);
	~FinalGameArea();

	Areas getAreaType();
	vector<IDrawAble*> getAreaVisualObjects();
	vector<IGameObject*> getAreaObjects();
	vector<Path*> getAreaPaths();
	vector<VisualEnemy*>* getAreaEnemies();
	Vector2u getAreaSize();
	void removeAreaObject(IGameObject *obj);
	void removeAreaEnemy(VisualEnemy *enemy);



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
};

