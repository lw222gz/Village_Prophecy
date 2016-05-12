#include "HostileGameArea.h"
#include "VisualEnemy.h"
#include "Path.h"


HostileGameArea::HostileGameArea(Vector2u size) 
	: areaSize(size)
{
	generateGameArea();
}


HostileGameArea::~HostileGameArea()
{
}


Areas HostileGameArea::getAreaType(){
	return Areas::Hostile;
}

vector<IDrawAble*> HostileGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

vector<GameObject*> HostileGameArea::getAreaObjects(){
	return areaObjects;
}

vector<Path*> HostileGameArea::getAreaPaths(){
	return areaPaths;
}

vector<VisualEnemy*>* HostileGameArea::getAreaEnemies(){
	return &enemies;
}

Vector2u HostileGameArea::getAreaSize(){
	return areaSize;
}


void HostileGameArea::generateGameArea(){
	Path *p = new Path(Areas::Base,
		Direction::East,
		Vector2f(areaSize.x, areaSize.y / 2));

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);

	p = new Path(Areas::Trigger_Final_Area,
		Direction::West,
		Vector2f(0, areaSize.y / 2));

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);

	VisualEnemy *e = new VisualEnemy(EnemyVisualType::Skeleton, Vector2f(areaSize.x - 400, areaSize.y - 500), 1);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);


	e = new VisualEnemy(EnemyVisualType::Skeleton, Vector2f(areaSize.x - 700, areaSize.y - 150), 0);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);

	e = new VisualEnemy(EnemyVisualType::Skeleton, Vector2f(areaSize.x - 1100, areaSize.y - 400), 5);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);

	e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(areaSize.x - 500, areaSize.y - 600), 6);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);
}

//doesnet contain any normal game object atm. causes an error when trying to remove a visualobject
void HostileGameArea::removeAreaObject(GameObject *obj){
	return;
	//areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	//areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	//delete obj;
}

void HostileGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}