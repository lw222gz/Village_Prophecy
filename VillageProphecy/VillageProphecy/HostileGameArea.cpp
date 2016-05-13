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
	path = new Path(Areas::Base,
		Direction::East,
		Vector2f(areaSize.x, areaSize.y / 2));

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	path = new Path(Areas::Trigger_Final_Area,
		Direction::West,
		Vector2f(0, areaSize.y / 2));

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	//initiates the area with a random amount of enemies between 1 and maxAmountOfEnemies
	SpawnEnemies(rand() % maxAmountOfEnemies + 1);
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

//respawns enemies and increases the level depending on the remaning
//amount of days.
void HostileGameArea::RespawnEnemies(int daysLeft){
	switch (daysLeft)
	{
		case 46:
			enemyMinLevels = 2;
			enemyMaxLevels = 4;		
			break;

		case 40:
			enemyMinLevels = 3;
			enemyMaxLevels = 6;
			break;

		case 30:
			enemyMinLevels = 6;
			enemyMaxLevels = 10;
			break;

		case 23:
			enemyMinLevels = 8;
			enemyMaxLevels = 14;
			break;

		case 15:
			enemyMinLevels = 16;
			enemyMaxLevels = 25;
			break;

		case 7:
			enemyMinLevels = 28;
			enemyMaxLevels = 40;
			break;
	}

	//spawns up to the max cap of enemies allowed;
	
	SpawnEnemies(rand() % (maxAmountOfEnemies - enemies.size() + 1));
}

//spawns enemies
void HostileGameArea::SpawnEnemies(int amount){
	for (int i = 0; i < amount; ++i){
		//if max amount of enemies are allreay in the area then no more will be added
		if (enemies.size() >= maxAmountOfEnemies){
			break;
		}

		//adds another enemy to the list
		enemy = new VisualEnemy(EnemyVisualType::Skeleton,
			//TODO: how can I access the width when setting the posotion? Should I do this in the object class
			getRandomCords(areaSize.x, areaSize.y, 120, 120),
			rand() % (enemyMaxLevels - enemyMinLevels + 1) + enemyMinLevels);

		enemies.push_back(enemy);
	}
}