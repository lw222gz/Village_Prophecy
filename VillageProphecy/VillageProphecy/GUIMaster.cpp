#include "GUIMaster.h"


GUIMaster::GUIMaster()
{
	//loads and sets textures
	if (!gameOverTexture.loadFromFile("Textures/PHGameOver.png")){
		throw "TEXTURE LOAD ERROR: Game over Texture did not load correctly";
	}
	gameOverSprite.setTexture(gameOverTexture);
	
	
	if (!inGameMenuTexture.loadFromFile("Textures/PHInGameMenu.png")){
		throw "TEXTURE LOAD ERROR: inGameMenu did not load correctly.";
	}
	inGameMenuSprite.setTexture(inGameMenuTexture);

	if (!quickMenuTexture.loadFromFile("Textures/PHQuickMenu.png")){
		throw "TEXTURE LOAD ERROR: quickMenu texture did not load correctly.";
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
void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window, View *gameView, Player *player, GameObject *triggerdObj, Time *t, int amountOfDaysLeft){
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
	if (triggerdObj != NULL && triggerdObj->getTriggerType() != TriggerType::No_Action){
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

		//If the object is constructable then the list of required items to construct is drawn.
		if (triggerdObj->getTriggerType() == TriggerType::Build){
			//Draw out required items for the construction
			displayText.setString("Requires:");
			displayText.setPosition(player->getPosition().x - 20,
				player->getPosition().y - quickMenuTexture.getSize().y + 40);
			window->draw(displayText);
			
			for (int i = 0; i < triggerdObj->MaterialListManager()->getMaterialList().size(); ++i){
				//Draw required items
				displayText.setString(to_string(triggerdObj->MaterialListManager()->getMaterialList()[i]->getAmountRequired()) + " " +
										getStringRepresentation(triggerdObj->MaterialListManager()->getMaterialList()[i]->getMaterialType()));
				displayText.setPosition(player->getPosition().x - 20,
										player->getPosition().y - quickMenuTexture.getSize().y + 60 + i*20);
				window->draw(displayText);
			}
		}
	}

	//lastly draw the player sprite to make sure that the player is allways visible.
	window->draw(player->getSprite());

	
	//Draw animation
	if (sleepAnimationActive){
		sleepAnimation(window, t);	
	}

	//draw amount of days left.
	displayText.setString("Amount of days left: " + to_string(amountOfDaysLeft));
	displayText.setPosition(gameView->getCenter().x - window->getSize().x/2,
							gameView->getCenter().y - window->getSize().y/2);
	window->draw(displayText);
}


template <class T>
string GUIMaster::getStringRepresentation(T enumValue){
	switch (enumValue)
	{
	case TriggerType::Loot:
		return "Loot";

	case TriggerType::Harvest:
		return "Harvest";

	case TriggerType::Interactable:
		return "Go To";

	case TriggerType::Build:
		return "Construct";

	case GameObjectType::Tree:
		return "Wood";

	case GameObjectType::Fireplace:
		return "Fireplace";

	case GameObjectType::Bed:
		return "Sleep";

	

	default:
		return "No string rep";
	}

}



void GUIMaster::activateSleepAnimation(Vector2f screenSize){
	sleepAnimationActive = true;
	rectPtr = new RectangleShape(screenSize);
	rectPtr->setFillColor(Color(0, 0, 0, 0));
	currentAnimationTime = 0;
	
}


//Animtion when the player goes to sleep
void GUIMaster::sleepAnimation(RenderWindow *window, Time *t){

	currentAnimationTime += t->asSeconds();
	//The precentAnimated will go up to 2 to easier handle the fade in and the fade out.
	float percentAnimated = currentAnimationTime / (sleepAnimationTime / 2);

	//if animation over it's interupted
	if (percentAnimated >= 2){
		sleepAnimationActive = false;
		delete rectPtr;
		return;
	}

	//Keeps the screen black for sleepTime(amount of seconds) to have a better sleep animation effect
	if (currentAnimationTime > sleepAnimationTime / 2 &&
		currentAnimationTime < sleepAnimationTime / 2 + sleepTime){
		//Keeps the screen black for sleepTime amount of seconds
		percentAnimated = 1;
	}
	else if (percentAnimated > 1){
		//Reverts the fade after the sleepTime animation
		//BUGG: Animation buggs out whenever the sleepAnimationTime is not an even number
		percentAnimated = ((sleepAnimationTime / 2.0) + (sleepTime / (sleepAnimationTime / 2.0))) - percentAnimated;
	}

	rectPtr->setFillColor(Color(0, 0, 0, 255 * percentAnimated));
	window->draw(*rectPtr);
}


float GUIMaster::getSleepAnimationTime(){
	return sleepAnimationTime;
}


void GUIMaster::DrawGameOver(RenderWindow *window, View *view){
	gameOverSprite.setPosition(view->getCenter().x - window->getSize().x/2,
								view->getCenter().y - window->getSize().y / 2);
	window->draw(gameOverSprite);
}