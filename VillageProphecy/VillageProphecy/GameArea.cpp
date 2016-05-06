#include "GameArea.h"

/*
* <DESCRIPTION>
* Constructor for the gamearea class, initiating a gamearea requires the 
* following parameters
* @PARAMS
* area: an enum value of the Areas enum, this is important as it will decide the contents of the game area
* size: a Vector2u that sets the size of the gamearea
*/
GameArea::GameArea(Areas area, Vector2u size) : areaType(area), areaSize(size)
{
	generateGameArea();
}


GameArea::~GameArea()
{
}

/*
* @RETURNS
* returns a vector of VisualEnemy pointers that are in the area.
*/
vector<VisualEnemy*>* GameArea::getAreaEnemies(){
	return &enemies;
}

/*
* @RETURNS
* returns a vector contaning all the visual objects in the game area.
*/
vector<IDrawAble*> GameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}


/*
* @RETURNS
* returns the area type of the game area.
*/
Areas GameArea::getAreaType(){
	return areaType;
}

/*
* @RETURNS
* returns a Vector2u representing the game area's size.
*/
Vector2u GameArea::getAreaSize(){
	return areaSize;
}


/*
* @RETURNS
* returns a vector contaning all the path objects for the game area.
*/
vector<Path*> GameArea::getAreaPaths(){
	return areaPaths;
}

/*
* @RETURNS
* returns the game objects of the game area.
*/
vector<GameObject*> GameArea::getAreaObjects(){
	return areaObjects;
}

/*
* <DESCRIPTION>
* Removes the given GameObject parameter from the game area.
* @PARAMS
* *obj: removes the object from the area.
*
* <EXTRA>
* remove formula found at : http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
*/
void GameArea::removeAreaObject(GameObject *obj){
	areaObjects.erase(remove(areaObjects.begin(), areaObjects.end(), obj), areaObjects.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), obj), areaVisualObjects.end());
	delete obj;
}


//removes a enemy game object
void GameArea::removeAreaEnemy(VisualEnemy *enemy){
	enemies.erase(remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	areaVisualObjects.erase(remove(areaVisualObjects.begin(), areaVisualObjects.end(), enemy), areaVisualObjects.end());
	delete enemy;
}


/*
* <DESCRIPTION>
* Generates the game areas objects and paths depending on the type of game area that is being created.
*/
void GameArea::generateGameArea(){
	
	switch (areaType)
	{
		case Areas::Base:{	
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
				
				
		
			break;
			}

		case Areas::Survival:{
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
			break;
			

		case Areas::Hostile:{
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

			e = new VisualEnemy(EnemyVisualType::Humans, Vector2f(areaSize.x - 500, areaSize.y -600), 6);
			areaVisualObjects.push_back(e);
			enemies.push_back(e);

		
		}
		break;

		case Areas::Final:{
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

			break;
		}

		default:
			break;
	}
}