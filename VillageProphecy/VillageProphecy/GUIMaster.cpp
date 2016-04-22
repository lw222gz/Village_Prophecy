#include "GUIMaster.h"

/*
* <DESCRIPTION>
* GUIMaster constructor.
* Initiates all general textures and fonts.
*/
GUIMaster::GUIMaster()
{
	//loads and sets textures
	if (!gameOverTexture.loadFromFile("Textures/PHGameOver.png")){
		throw "TEXTURE LOAD ERROR: Game over Texture did not load correctly";
	}
	gameOverSprite.setTexture(gameOverTexture);
	

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


/*
* <DESCRIPTION>
* Main function for drawing the game
*
* @PARAMS
* gameObject: a vector containg all the current visual game objects for the current game area.
* window: pointer to the game window object.
* gameView: pointer to the View object for the the game.
* triggerdobject: pointer to a GameObject that is triggerd, if no object is triggerd this is NULL.
* t: pointer to a Time object representing the time spent in the current iteration of the loop.
* amountOfDaysLeft: integer representing the amount of days left before gameover.
*/
void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window, View *gameView, Player *player, GameObject *triggerdObj, Time *t, int amountOfDaysLeft){
	//Optimize: Remove the need of reversing the vector
	//reverses the vector, thus items added first gets draw over items added after.
	sort(gameObjects.rbegin(), gameObjects.rend());

	for (int i = 0; i < gameObjects.size(); ++i){
		window->draw(gameObjects[i]->getSprite());
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


/*
* <DESCRIPTION>
* returns string representation depending on the given enum value given. If the givent value
* doesn't have a case "No string rep" will be returned.
*
* @PARAMS
* enumValue: template allows any kind of value.
*
* @RETURNS
* string that represents the given enum value.
*/
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


/*
* <DESCRIPTION>
* Activates and initates the values for the in-game sleep animation.
*
* @PARAMS
* screenSize: a Vector2f representing the size of the game window.
*/
void GUIMaster::activateSleepAnimation(Vector2f screenSize){
	sleepAnimationActive = true;
	rectPtr = new RectangleShape(screenSize);
	rectPtr->setFillColor(Color(0, 0, 0, 0));
	currentAnimationTime = 0;
	
}


/*
* <DESCRIPTION>
* Executes the sleep animation.
*
* @PARAMS
* window: pointer to the game window object.
* t: pointer to Time object representing time passd in the current iteration of the loop.
*/
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


/*
* @RETURNS
* returns the amount of seconds the sleep animation will take up.
*/
float GUIMaster::getSleepAnimationTime(){
	return sleepAnimationTime;
}


/*
* <DESCRIPTION>
* Draws the game over screen
*
* @PARAMS
* window: pointer to the game window object.
* view: pointer to the View object for the game.
*/
void GUIMaster::DrawGameOver(RenderWindow *window, View *view){
	gameOverSprite.setPosition(view->getCenter().x - window->getSize().x/2,
								view->getCenter().y - window->getSize().y / 2);
	window->draw(gameOverSprite);
}