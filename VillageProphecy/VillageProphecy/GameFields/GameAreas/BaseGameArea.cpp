#include "BaseGameArea.h"
#include "../Path.h"
#include "../../GameObjects/GameObject_HealingStation.h"

/*
* <DESCRIPTION>
* Constructor for the BaseGameARea class
* sets base values and calls the generateGameArea function
*
* @PARAMS
* size: a Vector2u representing the size for this game area.
* _texture: pointer to the TextureLoader object.
*/
BaseGameArea::BaseGameArea(Vector2u size, TextureLoader *_textures)
	: areaSize(size), textures(_textures)
{
	generateGameArea();
}


BaseGameArea::~BaseGameArea()
{
}

/*
* @RETURNS
* retunrs the area type.
*/
Areas BaseGameArea::getAreaType(){
	return Areas::Base;
}

/*
* @RETURNS
* returns the area visual objectss
*/
vector<IDrawAble*> BaseGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

/*
* @RETURNS
* returns the area game objects
*/
vector<IGameObject*> BaseGameArea::getAreaObjects(){
	return areaObjects;
}

/*
* @RETURNS
* returns the Path objects in this area.
*/
vector<Path*> BaseGameArea::getAreaPaths(){
	return areaPaths;
}

/*
* @RETURNS
* returns a pointer to the game areas VisualEnemy vector.
*/
vector<VisualEnemy*>* BaseGameArea::getAreaEnemies(){
	return &enemies;
}

/*
* @RETURNS
* returns a Vector2u representing the size of the game area
*/
Vector2u BaseGameArea::getAreaSize(){
	return areaSize;
}

/*
* <DESCRIPTION>
* Generates the base values for this game area
*/
void BaseGameArea::generateGameArea(){
	Path *p = new Path(Areas::Survival,
		Direction::East,
		Vector2f(areaSize.x, areaSize.y / 2),
		textures->getPathTexture());

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);


	p = new Path(Areas::Hostile,
		Direction::West,
		Vector2f(0, areaSize.y / 2),
		textures->getPathTexture());

	areaVisualObjects.push_back(p);
	areaPaths.push_back(p);
	
	firePlace = new GameObject_FirePlace(Vector2f(660, 390), textures->getFirePlaceTexture(), textures->getBurningFirePlaceTexture());
	areaObjects.push_back(firePlace);
	areaVisualObjects.push_back(firePlace);

	areaObjects.push_back(new GameObject_Bed(Vector2f(660, 280), textures->getBedTexture()));
	areaVisualObjects.push_back(areaObjects.back());

	areaObjects.push_back(new GameObject_HealingStation(Vector2f(200, 100), textures->getHealStationTexture()));
	areaVisualObjects.push_back(areaObjects.back());
}

/*
* <DESCRIPTION>
* Removes an area game object.
*
* @PARAMS
* obj: derived class object pointer of the IGameObject base class that is gonna be deleted.
*/
void BaseGameArea::removeAreaObject(IGameObject *obj){
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
void BaseGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}

/*
* <DESCRIPTION>
* Calls the fireplace burnout method as. 
* This method should only be called when the player goes to sleep and has a burning fireplace
*/
void BaseGameArea::firePlaceBurnOut(){
	firePlace->firePlaceBurnOut();
}

/*
* @RETURNS
* returns boolean representing if the player has a burning fireplace, true if the player has one
* otherwise false.
*/
bool BaseGameArea::playerHasBurningFirePlace(){
	if (firePlace->getObjectType() == Burning_Fireplace){
		return true;
	}
	return false;
}