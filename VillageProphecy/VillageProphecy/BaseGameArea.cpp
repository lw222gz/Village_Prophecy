#include "BaseGameArea.h"
#include "Path.h"
#include "GameObject.h"


BaseGameArea::BaseGameArea(Vector2u size) 
	: areaSize(size)
{
	generateGameArea();
}


BaseGameArea::~BaseGameArea()
{
}

Areas BaseGameArea::getAreaType(){
	return Areas::Base;
}

vector<IDrawAble*> BaseGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

vector<GameObject*> BaseGameArea::getAreaObjects(){
	return areaObjects;
}

vector<Path*> BaseGameArea::getAreaPaths(){
	return areaPaths;
}

vector<VisualEnemy*>* BaseGameArea::getAreaEnemies(){
	return &enemies;
}

Vector2u BaseGameArea::getAreaSize(){
	return areaSize;
}

void BaseGameArea::generateGameArea(){
	Path *p = new Path(Areas::Survival,
		Direction::East,
		Vector2f(areaSize.x, areaSize.y / 2));
	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);


	p = new Path(Areas::Hostile,
		Direction::West,
		Vector2f(0, areaSize.y / 2));

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);

	GameObject *go = new GameObject(GameObjectType::Fireplace, Vector2f(660, 390));
	areaVisualObjects.push_back(go);
	areaObjects.push_back(go);

	go = new GameObject(GameObjectType::Bed, Vector2f(660, 280));
	areaObjects.push_back(go);
	areaVisualObjects.push_back(go);
}

void BaseGameArea::removeAreaObject(GameObject *obj){
	areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	delete obj;
}

void BaseGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}



//returns true if the player has a burning fireplace
bool BaseGameArea::playerHasBurningFirePlace(){
	for (int i = 0; i < areaObjects.size(); ++i){
		if (areaObjects[i]->getObjectType() == Burning_Fireplace){
			return true;
		}
	}
	return false;
}