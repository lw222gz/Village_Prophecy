#include "GUIMaster.h"


GUIMaster::GUIMaster()
{
	//loads and sets textures
	if (!inGameMenuTexture.loadFromFile("Textures/PHInGameMenu.png")){
		throw "Texture: inGameMenu did not load correctly.";
	}
	inGameMenuSprite.setTexture(inGameMenuTexture);

	if (!quickMenuTexture.loadFromFile("Textures/PHQuickMenu.png")){
		throw "Texture: quickMenu texture did not load correctly.";
	}
	quickMenuSprite.setTexture(quickMenuTexture);
	//makes the quick menu semi transparent
	quickMenuSprite.setColor(Color(255, 255, 255, 128));

	if (!coolvetica.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}

	//Text settings
	displayText.setFont(coolvetica);
	displayText.setCharacterSize(16);
	displayText.setColor(Color::Black);
	//displayText.setStyle(Text::Bold);
}


GUIMaster::~GUIMaster()
{
}


//Draws the game
void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window, View *gameView, Player *player, GameObject *triggerdObj){
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

		//If an item is stackable the amount in the inventory is shown.
		if (player->InventoryManager()->getInventoryItems()[i]->isStackAble()){
			displayText.setString(to_string(player->InventoryManager()->getInventoryItems()[i]->getStackAmount()));
			displayText.setPosition(x + 55, y + 60);
			window->draw(displayText);
		}
		
	}

	//If triggerdObj isent null a quick menu should be displayed.
	if (triggerdObj != NULL){
		//sets the position for the quick menu
		quickMenuSprite.setPosition(player->getPosition().x + (player->getSize().x / 2) - quickMenuTexture.getSize().x / 2,
									player->getPosition().y - quickMenuTexture.getSize().y - 20);
		
		window->draw(quickMenuSprite);
		
		displayText.setString("Press 'R' to");
		displayText.setPosition(player->getPosition().x - 20,
			player->getPosition().y - quickMenuTexture.getSize().y);
		window->draw(displayText);

		displayText.setString(getStringRepresentation(triggerdObj->getTriggerType()) + " " + getStringRepresentation(triggerdObj->getObjectType()));
		displayText.setPosition(player->getPosition().x - 20,
								player->getPosition().y - quickMenuTexture.getSize().y + 20);
		window->draw(displayText);
	}

	//lastly draw the player sprite to make sure that the player is allways visible.
	window->draw(player->getSprite());
}


template <class T>
string GUIMaster::getStringRepresentation(T enumValue){
	switch (enumValue)
	{
	case TriggerType::Loot:
		return "Loot";

	case TriggerType::Harvest:
		return "Harvest";

	case GameObjectType::Tree:
		return "Wood";

	default:
		return "No string rep";
		break;
	}

}