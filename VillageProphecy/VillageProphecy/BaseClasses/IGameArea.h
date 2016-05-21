#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Enums/GameAreas.h"
#include "../Enemy/VisualEnemy.h"
#include "IGameObject.h"
#include "../GUI/TextureLoader.h"

class GameObject;
class Path;

using namespace std;
using namespace sf;

class IGameArea{
public:
	virtual Areas getAreaType() = 0;
	//Enemies are not added to the vector for VisualObjects as they need 
	//extra function calls.
	virtual vector<IDrawAble*> getAreaVisualObjects() = 0;
	virtual vector<VisualEnemy*>* getAreaEnemies() = 0;
	virtual vector<IGameObject*> getAreaObjects() = 0;
	virtual vector<Path*> getAreaPaths() = 0;
	virtual Vector2u getAreaSize() = 0;
	virtual void removeAreaObject(IGameObject *obj) = 0;
	virtual void removeAreaEnemy(VisualEnemy *enemy) = 0;
	virtual void generateGameArea() = 0;

protected:
	Vector2f getRandomCords(Vector2u areaSize, Vector2u pathSize, Vector2u textureSize);
	

private:
	//int values representing an extra indent when generating random cords.
	int spawnIndent = 75;
};