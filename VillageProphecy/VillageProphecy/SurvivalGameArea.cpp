#include "SurvivalGameArea.h"
#include "Path.h"
#include "GameObject.h"


SurvivalGameArea::SurvivalGameArea(Vector2u size) 
	: areaSize(size)
{
	generateGameArea();
}


SurvivalGameArea::~SurvivalGameArea()
{
}


Areas SurvivalGameArea::getAreaType(){
	return Areas::Survival;
}

vector<IDrawAble*> SurvivalGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

vector<GameObject*> SurvivalGameArea::getAreaObjects(){
	return areaObjects;
}

vector<Path*> SurvivalGameArea::getAreaPaths(){
	return areaPaths;
}

vector<VisualEnemy*>* SurvivalGameArea::getAreaEnemies(){
	return &enemies;
}

Vector2u SurvivalGameArea::getAreaSize(){
	return areaSize;
}

void SurvivalGameArea::generateGameArea(){
	Path *p = new Path(Areas::Base,
		Direction::West,
		Vector2f(0, areaSize.y / 2));

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);

	//TODO: randomize the object spawn. After gathering some should respawn 
	//after a certain amount of ingame days.
	GameObject *go = new GameObject(GameObjectType::Tree, Vector2f(500, 800));
	areaVisualObjects.push_back(go);
	areaObjects.push_back(go);

	go = new GameObject(GameObjectType::Tree, Vector2f(500, 200));
	areaVisualObjects.push_back(go);
	areaObjects.push_back(go);

	go = new GameObject(GameObjectType::Tree, Vector2f(700, 250));
	areaVisualObjects.push_back(go);
	areaObjects.push_back(go);

}

void SurvivalGameArea::removeAreaObject(GameObject *obj){
	areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	delete obj;
}

void SurvivalGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}
