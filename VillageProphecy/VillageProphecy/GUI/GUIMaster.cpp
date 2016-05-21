#include "GUIMaster.h"

/*
* <DESCRIPTION>
* GUIMaster constructor.
* Initiates all general textures and fonts.
*/
GUIMaster::GUIMaster(TextureLoader *_textures) 
	: textures(_textures)
{
	//loads and sets textures
	//TODO: set textures
	gameOverSprite.setTexture(*textures->getGameOverTexture());
	
	quickMenuSprite.setTexture(*textures->getQuickMenuTexture());
	//makes the quick menu semi transparent
	quickMenuSprite.setColor(Color(255, 255, 255, 128));

	
	gameWonSprite.setTexture(*textures->getGameWonTexture());	
	
	GrassBackgroundSprite.setTexture(*textures->getBackground_GrassTexture());

	//Text settings
	displayText.setFont(*textures->getCoolvecticaFont());
	displayText.setCharacterSize(16);
	displayText.setColor(Color::Black);
	//displayText.setStyle(Text::Bold);


	confirmationBox.setFillColor(Color::Magenta);
	confirmationBox.setSize(Vector2f(400, 100));

}


GUIMaster::~GUIMaster()
{
}


/*
* <DESCRIPTION>
* Draws a grass background for the combat phase of the game.
*
* @PARAMS
* window: pointer to the game window object
* view: pointer to the game View objec.t
*/
void GUIMaster::DrawGameCombatGrassBackground(RenderWindow *window, View *view){

	for (int y = (int)(view->getCenter().y - (window->getSize().y / 2)); 
		y < view->getCenter().y - (window->getSize().y / 2) + window->getSize().y; 
		y += (int)GrassBackgroundSprite.getLocalBounds().height){

		for (int x = (int)(view->getCenter().x - (window->getSize().x / 2));
			x < view->getCenter().x - (window->getSize().x / 2) + window->getSize().x;
			x += (int)GrassBackgroundSprite.getLocalBounds().width){

			GrassBackgroundSprite.setPosition((float)x, (float)y);
			window->draw(GrassBackgroundSprite);
		}
	}

}

/*
* <DESCRIPTION>
* Draws the game grass background
*
* @PARAMS
* window: pointer to the game window object
* area: pointer to the current game area object.
*/
void GUIMaster::DrawGameGrassBackground(RenderWindow *window, IGameArea *area){
	for (unsigned int y = 0; y < area->getAreaSize().y; y += (int)GrassBackgroundSprite.getLocalBounds().height){
		for (unsigned int x = 0; x < area->getAreaSize().x; x += (int)GrassBackgroundSprite.getLocalBounds().width){

			GrassBackgroundSprite.setPosition((float)x, (float)y);
			window->draw(GrassBackgroundSprite);
		}
	}
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
void GUIMaster::DrawGame(vector<IDrawAble*> gameObjects, vector<VisualEnemy*> *areaEnemies, RenderWindow *window, View *gameView,
						Player *player, IGameObject *triggerdObj, Time *t, int amountOfDaysLeft){

	//Optimize: Remove the need of reversing the vector
	//reverses the vector, thus items added first gets draw over items added after.
	sort(gameObjects.rbegin(), gameObjects.rend());

	for (unsigned int i = 0; i < gameObjects.size(); ++i){
		window->draw(gameObjects[i]->getSprite());
	}	

	//draw enemies, their names and levels
	for (unsigned int i = 0; i < areaEnemies->size(); ++i){
		window->draw(areaEnemies->at(i)->getSprite());
		displayText.setString("Lv " + to_string(areaEnemies->at(i)->getEnemyLevel()) + " " + getStringRepresentation(areaEnemies->at(i)->getType()));
		displayText.setPosition(areaEnemies->at(i)->getSprite().getPosition() - Vector2f(0, 25));
		window->draw(displayText);
	}

	//If triggerdObj isent null a quick menu should be displayed.
	if (triggerdObj != NULL && triggerdObj->getTriggerType() != TriggerType::No_Action){
		//sets the position for the quick menu
		quickMenuSprite.setPosition(player->getPosition().x + (player->getSize().x / 2) - quickMenuSprite.getTexture()->getSize().x / 2,
									player->getPosition().y - quickMenuSprite.getTexture()->getSize().y - 20);
		//draws quickmenu
		window->draw(quickMenuSprite);
		//draw text in quickmenu
		displayText.setString("Press 'R' to");
		displayText.setPosition(player->getPosition().x - 20,
			player->getPosition().y - quickMenuSprite.getTexture()->getSize().y);
		window->draw(displayText);

		displayText.setString(getStringRepresentation(triggerdObj->getTriggerType()) + " " + getStringRepresentation(triggerdObj->getObjectType()));
		displayText.setPosition(player->getPosition().x - 20,
								player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 20);
		window->draw(displayText);

		//draws requirements for objects that can be constructed.
		if (triggerdObj->getTriggerType() == TriggerType::Build){
			//Draw out required items for the construction
			displayText.setString("Requires:");
			displayText.setPosition(player->getPosition().x - 20,
				player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 40);
			window->draw(displayText);
			
			for (unsigned int i = 0; i < triggerdObj->MaterialListManager()->getMaterialList().size(); ++i){
				//Draw required items
				displayText.setString(to_string(triggerdObj->MaterialListManager()->getMaterialList()[i]->getAmountRequired()) + " " +
										getStringRepresentation(triggerdObj->MaterialListManager()->getMaterialList()[i]->getMaterialType()));
				displayText.setPosition(player->getPosition().x - 20,
					player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 60 + i * 20);
				window->draw(displayText);
			}
		}

		//if the game object is useable the any required item to use it is displayed
		else if (triggerdObj->getTriggerType() == Usable){
			displayText.setString("Requires:");
			displayText.setPosition(player->getPosition().x - 20,
				player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 40);
			window->draw(displayText);

			displayText.setString("1 " + getStringRepresentation(triggerdObj->getConsumptionType()));
			displayText.setPosition(player->getPosition().x - 20,
									player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 60);
			window->draw(displayText);
		}

		//draws requirements for objects that can be set on fire
		else if (triggerdObj->getTriggerType() == Set_On_Fire){
			displayText.setString("Requires:");
			displayText.setPosition(player->getPosition().x - 20,
									player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 40);
			window->draw(displayText);

			displayText.setString("Skill: Fireball");
			displayText.setPosition(player->getPosition().x - 20,
									player->getPosition().y - quickMenuSprite.getTexture()->getSize().y + 60);
			window->draw(displayText);
		}
	}

	//draw alert messages
	for (unsigned int i = 0; i < gameAlerts.size(); ++i){

		gameAlerts[i]->DrawMessage(window, t->asSeconds());
		//removes a message if it's lifetime has expierd.
		if (gameAlerts[i]->getLifeTimePercent() >= 1){
			delete gameAlerts[i];
			gameAlerts.erase(gameAlerts.begin() + i);
		}
	}



	//lastly draw the player sprite to make sure that the player is allways visible.
	//ANYTHING BELOW THIS POINT HAS PRIORITY OVER THE PLAYER IN THE DRAW ORDER.
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

		case TriggerType::Set_On_Fire:
			return "Ignite";

		case TriggerType::Usable:
			return "Use";

		case GameObjectType::Tree:
			return "Wood";

		case GameObjectType::Fireplace:
			return "Fireplace";

		case GameObjectType::Bed:
			return "Sleep";

		case GameObjectType::HealingStation:
			return "Healing station";

		case EnemyVisualType::Skeleton:
			return "Skeleton";

		case EnemyVisualType::Humans:
			return "Human"; 

		case EnemyVisualType::Executioner:
			return "Executioner";



		default:
			return "No string rep";
	}

}

/*
* <DESCRIPTION>
* Draws a confirmation box, this is used when the player is about to do something
* that cant be reversed. 
*
* @PARAMS
* window: pointer to the game window object.
* view: pointer to the game view object.
* question: string representation of the statement the player must confirm or deny.
*/
void GUIMaster::DrawConfirmationBox(RenderWindow *window, View *view, string question){
	confirmationBox.setPosition(view->getCenter().x - confirmationBox.getSize().x / 2, view->getCenter().y - window->getSize().y / 3);

	screenCoverRect.setSize((Vector2f)window->getSize());
	screenCoverRect.setFillColor(Color(0, 0, 0, 125));
	screenCoverRect.setPosition(Vector2f(view->getCenter().x - window->getSize().x / 2, view->getCenter().y - window->getSize().y / 2));

	window->draw(screenCoverRect);
	window->draw(confirmationBox);

	displayText.setPosition(confirmationBox.getPosition().x + 15, confirmationBox.getPosition().y + 15);
	displayText.setString(question);
	window->draw(displayText);


	displayText.setString("Press Enter to confirm, Backspace to deny.");
	displayText.setPosition(displayText.getPosition().x, displayText.getPosition().y + 25);
	window->draw(displayText);
}


/*
* <DESCRIPTION>
* Activates and initates the values for the in-game sleep animation.
*
* @PARAMS
* screenSize: a Vector2f representing the size of the game window.
*/
void GUIMaster::activateSleepAnimation(Vector2f screenSize, bool hasFire){
	sleepMessage = "You slept through the night. \n";
	if (!hasFire){
		sleepMessage += "You had no fire to warm your body during the cold night. Health lost. \n";
	}

	sleepAnimationActive = true;
	screenCoverRect.setSize(screenSize);
	screenCoverRect.setFillColor(Color(0, 0, 0, 0));
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

	window->draw(screenCoverRect);
	currentAnimationTime += t->asSeconds();

	//fade in time has to be lower than sleepTime
	if (currentAnimationTime <= sleepFadeTime){
		screenCoverRect.setFillColor(Color(0, 0, 0, (int)(255 * currentAnimationTime / sleepFadeTime)));
	}
	//sleepTime has to be lower than sleepFadeBackTime
	else if (currentAnimationTime <= sleepTime){

		screenCoverRect.setFillColor(Color(0, 0, 0, 255));
		displayText.setColor(Color::White);

		displayText.setString(sleepMessage);
		window->draw(displayText);

		displayText.setColor(Color::Black);
		
	}
	//when animation time passes the sleepFadeBackTime the animation är över.
	else if (currentAnimationTime < sleepFadeBackTime){
		screenCoverRect.setFillColor(Color(0, 0, 0, (int)(255 * (1 - (currentAnimationTime - sleepTime) / (currentAnimationTime - sleepFadeTime)))));
	}
	else {
		sleepAnimationActive = false;
		return;
	}	
}


/*
* @RETURNS
* returns the amount of seconds the sleep animation will take up.
*/
float GUIMaster::getSleepAnimationTime(){
	return sleepFadeBackTime;
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

/*
* <DESCRIPTION>
* Draws a game won display.
*
* @PARAMS
* window: pointer to the game window object.
* view: pointer to the game view object.
*/
void GUIMaster::DrawGameWon(RenderWindow *window, View *view){
	gameWonSprite.setPosition(view->getCenter().x - window->getSize().x / 2,
								view->getCenter().y - window->getSize().y / 2);
	window->draw(gameWonSprite);
}

/*
* <DESCRIPTION>
* Adds a GameAlert message. This is used on giving the player an error or waring alert.
*
* @PARAMS
* mess: string representation of the message to display.
* position: a Vector2f position that the message will spawn on.
*/
void GUIMaster::AddGameAlert(string mess, Vector2f position){
	gameAlerts.push_back(new GameMessage(mess, position, 1.25, textures->getCoolvecticaFont(), 16));
}