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
	path = new Path(Areas::Base,
					Direction::West,
					Vector2f(0, areaSize.y / 2));

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	//spawns 2-10 trees as intializer. 2 trees are required to build a campfire.
	SpawnTrees(rand() % (maxAmountOfTrees - 2 + 1) + 2);

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


void SurvivalGameArea::RespawnResources(int amountOfDaysLeft){
	//TODO: based on 
	if (areaObjects.size() < maxAmountOfTrees){
		if (seed.amountOfTrees == 0){
			GrowTrees(amountOfDaysLeft);
		}	
	}

	if (seed.dayOfSprout == amountOfDaysLeft){
		SpawnTrees(seed.amountOfTrees);
		//resets the seed
		seed.amountOfTrees = 0;
		seed.dayOfSprout = 0;
	}
}

//initiates seeds that will sprout 3 days later.
void SurvivalGameArea::GrowTrees(int amountOfDaysLeft){
	seed.dayOfSprout = amountOfDaysLeft - 3;
	seed.amountOfTrees = rand() % (maxAmountOfTrees - areaObjects.size()) + 1;
}

//spawns trees as long as it wont override the limit of trees
void SurvivalGameArea::SpawnTrees(int amount){

	for (int i = 0; i < amount; ++i){
		//if max amount is allready spawned then the game wont spawn more
		if (areaObjects.size() >= maxAmountOfTrees){
			break;
		}

		//TODO: how can I access the width when setting the posotion? Should I do this in the object class
		//spawns a tree
		gameObj = new GameObject(GameObjectType::Tree, 
								getRandomCords(areaSize.x, areaSize.y, 100, 100));

		areaVisualObjects.push_back(gameObj);
		areaObjects.push_back(gameObj);
	}
}
