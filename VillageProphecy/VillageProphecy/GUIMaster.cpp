#include "GUIMaster.h"


GUIMaster::GUIMaster()
{
}


GUIMaster::~GUIMaster()
{
}


void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window){
	//Optimize: Remove the need of reversing the vector
	//reverses the vector, thus items added first gets draw over items added after.
	std::sort(gameObjects.rbegin(), gameObjects.rend());

	for (int i = 0; i < gameObjects.size(); ++i){
		window->draw(gameObjects[i]->getSprite());
	}	
}