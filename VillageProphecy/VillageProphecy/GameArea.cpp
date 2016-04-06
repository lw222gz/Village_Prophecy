#include "GameArea.h"


GameArea::GameArea(Areas area, Vector2u size) : areaType(area), areaSize(size)
{
	generateGameArea();
}


GameArea::~GameArea()
{
}

vector<IDrawAble*> GameArea::getAreaObjects(){
	return areaObjects;
}

Areas GameArea::getAreaType(){
	return areaType;
}

Vector2u GameArea::getAreaSize(){
	return areaSize;
}

vector<Path*> GameArea::getAreaPaths(){
	return areaPaths;
}


void GameArea::generateGameArea(){
	
	switch (areaType)
	{
		case Areas::Base:{	
				Path *p = new Path(Areas::Survival,
									Direction::East,
									Vector2f(areaSize.x, areaSize.y / 2));
				areaObjects.push_back(p);
				areaPaths.push_back(p);
				

				p = new Path(Areas::Hostile,
							Direction::West,
							Vector2f(0, areaSize.y / 2));

				areaObjects.push_back(p);
				areaPaths.push_back(p);
				
				
		
			break;
			}

		case Areas::Survival:{
			Path *p = new Path(Areas::Base,
								Direction::West,
								Vector2f(0, areaSize.y / 2));

			areaObjects.push_back(p);
			areaPaths.push_back(p);

			}
			break;
			

		case Areas::Hostile:{
			Path *p = new Path(Areas::Base,
							Direction::East,
							Vector2f(areaSize.x, areaSize.y / 2));

			areaObjects.push_back(p);
			areaPaths.push_back(p);

		
		}
		break;

		default:
			break;
	}
}