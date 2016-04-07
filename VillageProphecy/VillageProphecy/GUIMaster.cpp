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


//Draws the game
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

	//TODO: Bugg makes the inventory slots "bounce around" abit when moving.
	int x = inGameMenuSprite.getPosition().x + 1060;
	int y = inGameMenuSprite.getPosition().y + 15;
	for (int i = 0; i < player->InventoryManager()->getInventoryItems().size(); ++i){		
		if (i == 3){
			y = inGameMenuSprite.getPosition().y + 105;
		}
		if (i == 3){
			x = inGameMenuSprite.getPosition().x + 1060;
		}

		x += 90;


		player->InventoryManager()->getInventoryItems()[i]->setSlotPosition(Vector2f(x, y));
		window->draw(player->InventoryManager()->getInventoryItems()[i]->getSprite());		
		
	}
	
	//lastly draw the player sprite to make sure that the player is allways visible.
	window->draw(player->getSprite());
}