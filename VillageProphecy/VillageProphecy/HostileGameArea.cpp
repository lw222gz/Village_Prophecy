#include "HostileGameArea.h"
#include "VisualEnemy.h"
#include "Path.h"

/*
* <DESCRIPTION>
* Constructor for the HostileGameArea class
* sets base values and call the generateGameArea function
*
* @PARAMS
* size: a Vector2u representing the size for this game area.
* _texture: pointer to the TextureLoader object.
*/
HostileGameArea::HostileGameArea(Vector2u size, TextureLoader *_textures)
	: areaSize(size), textures(_textures)
{
	generateGameArea();
}


HostileGameArea::~HostileGameArea()
{
}

/*
* @RETURNS
* retunrs the area type.
*/
Areas HostileGameArea::getAreaType(){
	return Areas::Hostile;
}

/*
* @RETURNS
* returns the area visual objectss
*/
vector<IDrawAble*> HostileGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

/*
* @RETURNS
* returns the area game objects
*/
vector<IGameObject*> HostileGameArea::getAreaObjects(){
	return areaObjects;
}

/*
* @RETURNS
* returns the Path objects in this area.
*/
vector<Path*> HostileGameArea::getAreaPaths(){
	return areaPaths;
}

/*
* @RETURNS
* returns a pointer to the game areas VisualEnemy vector.
*/
vector<VisualEnemy*>* HostileGameArea::getAreaEnemies(){
	return &enemies;
}

/*
* @RETURNS
* returns a Vector2u representing the size of the game area
*/
Vector2u HostileGameArea::getAreaSize(){
	return areaSize;
}

/*
* <DESCRIPTION>
* Generates the base values for this game area
*/
void HostileGameArea::generateGameArea(){
	path = new Path(Areas::Base,
		Direction::East,
		Vector2f(areaSize.x, areaSize.y / 2),
		textures->getPathTexture());

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	path = new Path(Areas::Trigger_Final_Area,
		Direction::West,
		Vector2f(0, areaSize.y / 2),
		textures->getPathTexture());

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	//initiates the area with a random amount of enemies between 1 and maxAmountOfEnemies
	SpawnEnemies(rand() % maxAmountOfEnemies + 1);
}

/*
* TODO: Fix bugg:
* As this area has no game objects a compiling error is caused whenever the normal code for 
* removing a game object
*/
void HostileGameArea::removeAreaObject(IGameObject *obj){
	return;
	//areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	//areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	//delete obj;
}

/*
* <DESCRIPTION>
* Removes an area VisualEnemy object.
*
* @PARAMS
* enemy: pointer to the VisualEnemy object to remove.
*/
void HostileGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}

/*
* <DESCRIPTION>
* Increases the level of enemies that spawn depending on the amount of days left.
* Also spawns calls SpawnEnemies to spawn a random amount of enemies between 1 and 
* 
*
* @PARAMS 
* daysLeft: integer representing the amount of days left before game over.
*/
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

/*
* <DESCRIPTION>
* Spawns enemies as long as the amount to spawn does not override the max limit.
*
* @PARAMS
* amount: integer representing the amount of enemies that is to be spawned.
*/
void HostileGameArea::SpawnEnemies(int amount){
	for (int i = 0; i < amount; ++i){
		//if max amount of enemies are allreay in the area then no more will be added
		if (enemies.size() >= maxAmountOfEnemies){
			break;
		}

		//adds another enemy to the list
		enemy = new VisualEnemy(EnemyVisualType::Skeleton,
			//TODO: how can I access the width when setting the posotion? Should I do this in the object class
			getRandomCords(areaSize, 
						   textures->getPathTexture()->getSize(), 
						   textures->getSkeletonTexture()->getSize()),
			rand() % (enemyMaxLevels - enemyMinLevels + 1) + enemyMinLevels,
			textures);

		enemies.push_back(enemy);
	}
}