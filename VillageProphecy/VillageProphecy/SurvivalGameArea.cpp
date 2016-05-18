#include "SurvivalGameArea.h"
#include "Path.h"
#include "GameObject_Tree.h"

/*
* <DESCRIPTION>
* Constructor for the SurvivalGameArea class
* sets base values and call the generateGameArea function
*
* @PARAMS
* size: a Vector2u representing the size for this game area.
* _texture: pointer to the TextureLoader object.
*/
SurvivalGameArea::SurvivalGameArea(Vector2u size, TextureLoader *_textures) 
	: areaSize(size), textures(_textures)
{
	generateGameArea();
}


SurvivalGameArea::~SurvivalGameArea()
{
}


/*
* @RETURNS
* retunrs the area type.
*/
Areas SurvivalGameArea::getAreaType(){
	return Areas::Survival;
}

/*
* @RETURNS
* returns the area visual objectss
*/
vector<IDrawAble*> SurvivalGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

/*
* @RETURNS
* returns the area game objects 
*/
vector<IGameObject*> SurvivalGameArea::getAreaObjects(){
	return areaObjects;
}

/*
* @RETURNS
* returns the Path objects in this area.
*/
vector<Path*> SurvivalGameArea::getAreaPaths(){
	return areaPaths;
}

/*
* @RETURNS
* returns a pointer to the game areas VisualEnemy vector.
*/
vector<VisualEnemy*>* SurvivalGameArea::getAreaEnemies(){
	return &enemies;
}

/*
* @RETURNS
* returns a Vector2u representing the size of the game area
*/
Vector2u SurvivalGameArea::getAreaSize(){
	return areaSize;
}

/*
* <DESCRIPTION>
* Generates the base values for this game area
*/
void SurvivalGameArea::generateGameArea(){
	path = new Path(Areas::Base,
					Direction::West,
					Vector2f(0, areaSize.y / 2),
					textures->getPathTexture());

	areaVisualObjects.push_back(path);
	areaPaths.push_back(path);

	//spawns 2-10 trees as intializer. 2 trees are required to build a campfire.
	SpawnTrees(rand() % (maxAmountOfTrees - 2 + 1) + 2);

}

/*
* <DESCRIPTION>
* Removes an area game object.
*
* @PARAMS
* obj: derived class object pointer of the IGameObject base class that is gonna be deleted.
*/
void SurvivalGameArea::removeAreaObject(IGameObject *obj){
	areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	delete obj;
}

/*
* <DESCRIPTION>
* Removes an area VisualEnemy object.
*
* @PARAMS
* enemy: pointer to the VisualEnemy object to remove.
*/
void SurvivalGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}


/*
* <DESCRIPTION>
* Initiates a Seed struct if one is not allready set,
* If a seed is on it's day to sprout this method will spawn those trees
* and reset the seed struct.
*
* @PARAMS
* amountOfDaysLeft: integer representing the amount of days left before game over.
*/
void SurvivalGameArea::RespawnResources(int amountOfDaysLeft){
	//TODO: based on 
	if (areaObjects.size() < maxAmountOfTrees){
		if (seed.amountOfTrees == 0){
			PlantSeeds(amountOfDaysLeft);
		}	
	}

	if (seed.dayOfSprout == amountOfDaysLeft){
		SpawnTrees(seed.amountOfTrees);
		//resets the seed
		seed.amountOfTrees = 0;
		seed.dayOfSprout = 0;
	}
}

/*
* <DESCRIPTION>
* Initates the values for the Seed struct to have it sprout new trees in 3 days.
*
* @PARAMS
* amountOfDaysLeft: integer representing the amount of days left before game over.
*/
void SurvivalGameArea::PlantSeeds(int amountOfDaysLeft){
	seed.dayOfSprout = amountOfDaysLeft - 3;
	seed.amountOfTrees = rand() % (maxAmountOfTrees - areaObjects.size()) + 1;
}

/*
* <DESCRIPTION>
* Spawns trees based on parameter as long as it does not overirde the max limit.
*
* @PARAMS
* amount: integer representing the amount of trees that are gonna spawn.
*/
void SurvivalGameArea::SpawnTrees(int amount){

	for (int i = 0; i < amount; ++i){
		//if max amount is allready spawned then the game wont spawn more
		if (areaObjects.size() >= maxAmountOfTrees){
			break;
		}
			
		areaObjects.push_back(new GameObject_Tree(
							getRandomCords(areaSize, 
											textures->getPathTexture()->getSize(), 
											textures->getWoodObjectTexture()->getSize()),
							textures->getWoodObjectTexture()));

		areaVisualObjects.push_back(areaObjects.back());
		
	}
}
