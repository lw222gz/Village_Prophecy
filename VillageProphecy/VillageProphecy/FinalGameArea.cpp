#include "FinalGameArea.h"
#include "VisualEnemy.h"


FinalGameArea::FinalGameArea(Vector2u size) 
	: areaSize(size)
{
	generateGameArea();
}


FinalGameArea::~FinalGameArea()
{
}


Areas FinalGameArea::getAreaType(){
	return Areas::Final;
}

vector<IDrawAble*> FinalGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

vector<GameObject*> FinalGameArea::getAreaObjects(){
	return areaObjects;
}

vector<Path*> FinalGameArea::getAreaPaths(){
	return areaPaths;
}

vector<VisualEnemy*>* FinalGameArea::getAreaEnemies(){
	return &enemies;
}

Vector2u FinalGameArea::getAreaSize(){
	return areaSize;
}

void FinalGameArea::generateGameArea(){
	VisualEnemy *e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(500, 60), 5);
	/*areaVisualObjects.push_back(e);
	enemies.push_back(e);

	e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(200, 60), 5);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);

	e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(700, 60), 5);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);*/

	e = new VisualEnemy(EnemyVisualType::Executioner, Vector2f(0, 10), 2);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);
}


//doesnet contain any normal game object atm. causes an error when trying to remove a visualobject
void FinalGameArea::removeAreaObject(GameObject *obj){
	return;
	//areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	//areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	//delete obj;
}

void FinalGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}