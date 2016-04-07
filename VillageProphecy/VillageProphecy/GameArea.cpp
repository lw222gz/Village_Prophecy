#include "GameArea.h"


GameArea::GameArea(Areas area, Vector2u size) : areaType(area), areaSize(size)
{
	generateGameArea();
}


GameArea::~GameArea()
{
}

vector<IDrawAble*> GameArea::getAreaVisualObjects(){
	return areaVisualObjects;
}

Areas GameArea::getAreaType(){
	return areaType;
}

//returns a Vector2u representing the 
Vector2u GameArea::getAreaSize(){
	return areaSize;
}

//returns the path objects in the area
vector<Path*> GameArea::getAreaPaths(){
	return areaPaths;
}

//returnes the game objects in the area
vector<GameObject*> GameArea::getAreaObjects(){
	return areaObjects;
}


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

			}
			break;
			

		case Areas::Hostile:{
			Path *p = new Path(Areas::Base,
							Direction::East,
							Vector2f(areaSize.x, areaSize.y / 2));

			areaVisualObjects.push_back(p);
			areaPaths.push_back(p);

		
		}
		break;

		default:
			break;
	}
}