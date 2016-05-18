#include "FinalGameArea.h"
#include "VisualEnemy.h"

/*
* <DESCRIPTION>
* Constructor for the FinalGameArea class
* sets base values and call the generateGameArea function
*
* @PARAMS
* size: a Vector2u representing the size for this game area.
* _texture: pointer to the TextureLoader object.
*/
FinalGameArea::FinalGameArea(Vector2u size, TextureLoader *_textures)
	: areaSize(size), textures(_textures)
{
	generateGameArea();
}


FinalGameArea::~FinalGameArea()
{
}


/*
* @RETURNS
* retunrs the area type.
*/
Areas FinalGameArea::getAreaType(){
	return Areas::Final;
}

/*
* @RETURNS
* returns the area visual objectss
*/
vector<IDrawAble*> FinalGameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

/*
* @RETURNS
* returns the area game objects
*/
vector<IGameObject*> FinalGameArea::getAreaObjects(){
	return areaObjects;
}

/*
* @RETURNS
* returns the Path objects in this area.
*/
vector<Path*> FinalGameArea::getAreaPaths(){
	return areaPaths;
}

/*
* @RETURNS
* returns a pointer to the game areas VisualEnemy vector.
*/
vector<VisualEnemy*>* FinalGameArea::getAreaEnemies(){
	return &enemies;
}

/*
* @RETURNS
* returns a Vector2u representing the size of the game area
*/
Vector2u FinalGameArea::getAreaSize(){
	return areaSize;
}

/*
* <DESCRIPTION>
* Generates the base values for this game area
*/
void FinalGameArea::generateGameArea(){
	enemies.push_back(new VisualEnemy(EnemyVisualType::Humans, Vector2f(500, 60), 5, textures));
	areaVisualObjects.push_back(enemies.back());
	
	/*e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(200, 60), 5);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);

	e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(700, 60), 5);
	areaVisualObjects.push_back(e);
	enemies.push_back(e);*/

	enemies.push_back(new VisualEnemy(EnemyVisualType::Executioner, Vector2f(0, 10), 2, textures));
	areaVisualObjects.push_back(enemies.back());
	
}

/*
* TODO: Fix bugg:
* As this area has no game objects a compiling error is caused whenever the normal code for
* removing a game object
*/
void FinalGameArea::removeAreaObject(IGameObject *obj){
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
void FinalGameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}