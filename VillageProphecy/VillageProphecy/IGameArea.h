#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameAreas.h"
#include "VisualEnemy.h"

class GameObject;
class Path;

using namespace std;
using namespace sf;

class IGameArea{
public:
	virtual Areas getAreaType() = 0;
	virtual vector<IDrawAble*> getAreaVisualObjects() = 0;
	virtual vector<GameObject*> getAreaObjects() = 0;
	virtual vector<Path*> getAreaPaths() = 0;
	virtual vector<VisualEnemy*>* getAreaEnemies() = 0;
	virtual Vector2u getAreaSize() = 0;
	virtual void removeAreaObject(GameObject *obj) = 0;
	virtual void removeAreaEnemy(VisualEnemy *enemy) = 0;
	virtual void generateGameArea() = 0;

protected:
	Vector2f getRandomCords(int areaWidth, int areaHeight, float textureWidth, float textureHeight);
	
};