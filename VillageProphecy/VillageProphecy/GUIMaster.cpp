#include "GUIMaster.h"


GUIMaster::GUIMaster()
{
	if (!inGameMenuTexture.loadFromFile("Textures/PHInGameMenu.png")){
		throw "Texture: inGameMenu did not load correctly.";
	}
	inGameMenuSprite.setTexture(inGameMenuTexture);
	//inGameMenuSprite.setPosition(0, 700);
}


GUIMaster::~GUIMaster()
{
}


void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window, View *gameView, Player *player){
	//Optimize: Remove the need of reversing the vector
	//reverses the vector, thus items added first gets draw over items added after.
	sort(gameObjects.rbegin(), gameObjects.rend());

	for (int i = 0; i < gameObjects.size(); ++i){
		window->draw(gameObjects[i]->getSprite());
	}	
	
	inGameMenuSprite.setPosition(gameView->getCenter().x - window->getSize().x / 2,
		gameView->getCenter().y + window->getSize().y / 2 - 200);
	window->draw(inGameMenuSprite);

	int x = 0;
	int y = 0;
	for (int i = 0; i < player->InventoryManager()->getInventoryItems().size(); ++i){
		x = i * 80;
		//TODO: draw inventory spots.
	}


	window->draw(player->getSprite());
}