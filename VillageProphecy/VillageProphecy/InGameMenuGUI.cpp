#include "InGameMenuGUI.h"

/*
* <DESCRIPTION>
* Constructor for the InGameMenuGUI class
* Sets any general textures for the game menu
* Initiates all RectangleShape objects for the bars that can be displayed
* Sets Text font and base values
*
* @PARAMS
* gameView: pointer to the View object for the game.
*/
InGameMenuGUI::InGameMenuGUI(View *gameView) : view(gameView)
{
	if (!optionPointerTexture.loadFromFile("Textures/PHOptionPointer.png")){
		throw "TEXTURE LOAD ERROR: Option poitner texture did not load correctly.";
	}
	optionPointerSprite.setTexture(optionPointerTexture);

	if (!inGameMenuTexture.loadFromFile("Textures/PHInGameMenu.png")){
		throw "TEXTURE LOAD ERROR: inGameMenu did not load correctly.";
	}
	inGameMenuSprite.setTexture(inGameMenuTexture);

	//Sets status bar colors.
	behindHPBar.setSize(Vector2f(250, 40));
	behindHPBar.setFillColor(Color::Red);

	hpBar.setFillColor(Color::Green);

	behindStatBar.setSize(Vector2f(150, 10));
	behindStatBar.setFillColor(Color(64, 64, 64, 255));

	statBar.setFillColor(Color(255, 165, 0, 255));

	//TODO:-optimize- already loaded in GUIMaster.cpp 
	if (!coolvetica.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}
	//Text settings
	displayText.setFont(coolvetica);
	displayText.setCharacterSize(16);
	displayText.setColor(Color::Black);
	//displayText.setStyle(Text::Bold);

	XPBar.setSize(Vector2f(150, 10));
	behindXPBar.setSize(Vector2f(150, 10));

	XPBar.setFillColor(Color(75, 0, 130, 255));
	behindXPBar.setFillColor(Color::Black);
}


InGameMenuGUI::~InGameMenuGUI()
{
}

/*
* <DESCRIPTION>
* Calls methods for drawing the normal game mode game menu.
*
* @PARAMS
* window: pointer to the game window object.
* player: pointer to the game Player object.
*/
void InGameMenuGUI::DrawGameMenu(RenderWindow *window, Player *player){
	DrawBaseMenu(window);

	DrawPlayerInventory(window, player);

	DrawXPBar(window, player);

	DrawPlayerActionPoints(window, player);

	DrawPlayerStats(window, player);
}


/*
* <DESCRIPTION>
* Calls methods for drawing the combat game menu
*
* @PARAMS
* window: pointer to the game window object
* player: pointer to the game Player game object.
* currentOption: CombatOptions enum value representing the current option the player is deciding on.
*/
void InGameMenuGUI::DrawCombatMenu(RenderWindow *window, Player *player, CombatOptions *currentOption){
	DrawBaseMenu(window);

	DrawPlayerInventory(window, player);
	
	DrawPlayerStats(window, player);

	DrawCombatOptions(window, currentOption);
}


/*
* <DESCRIPTION>
* Draws the player EXP bar
*
* @PARAMS
* window: pointer to the game window object.
* player: pointer to the game Player object.
*/
void InGameMenuGUI::DrawXPBar(RenderWindow *window, Player *player){
	ResetTransformation(window->getSize());
	transformation.translate(300, 150);

	window->draw(behindXPBar, transformation);

	XPBar.setSize(Vector2f(behindXPBar.getSize().x * ((float)player->StatsManager()->getTotalExp() / (float)player->StatsManager()->getNextLevelExp()), 
							XPBar.getSize().y));

	window->draw(XPBar, transformation);

	displayText.setCharacterSize(26);
	displayText.setString("Level: " + getStringRepPlayerLevel(player->StatsManager()->getCurrentLevel()));
	transformation.translate(0, -36);
	window->draw(displayText, transformation);
	transformation.translate(0, 36);

	displayText.setCharacterSize(16);
	transformation.translate(-25, -5);
	displayText.setString("XP:");
	window->draw(displayText, transformation);
	transformation.translate(25, 5);

	transformation.translate(150, -5);
	displayText.setString(to_string(player->StatsManager()->getTotalExp()) + " / " + to_string(player->StatsManager()->getNextLevelExp()));
	window->draw(displayText, transformation);
	
}

/*
* @RETURNS
* string representation of the players current level.
*/
string InGameMenuGUI::getStringRepPlayerLevel(LevelEXPRequirement currlevel){
	switch (currlevel)
	{
	case LEVEL_0:
		return "0";

	case LEVEL_1:
		return "1";

	case LEVEL_2:
		return "2";

	case LEVEL_3:
		return "3";

	case LEVEL_30:
		return "MAX";

	default:
		return "No defined level";
	}
}

/*
* <DESCRIPTION>
* Resets the transformation object and sets it's position to the left top of the screen.
*
* @PARAMS
* windowSize: Vector2u representing the size of the game window
*/
void InGameMenuGUI::ResetTransformation(Vector2u windowSize){
	transformation.translate(-transformation.transformPoint(0, 0));
	transformation.translate(view->getCenter().x - windowSize.x / 2,
							view->getCenter().y + windowSize.y / 2 - 200);
}

/*
* <DESCRIPTION>
* Draws the base menu background
*
* @PARAMS
* window: pointer to the game window object.
*/
void InGameMenuGUI::DrawBaseMenu(RenderWindow *window){
	ResetTransformation(window->getSize());
	window->draw(inGameMenuSprite, transformation);
}


/*
* <DESCRIPTION>
* Draws the player stats. Hit points, hunger points, mood points and stamina points.
*
* @PARAMS
* window: pointer to the game window object.
* player: pointer to the game Player object.
*/
void InGameMenuGUI::DrawPlayerStats(RenderWindow *window, Player *player){
	ResetTransformation(window->getSize());
	//#START DRAW Player hit points
	transformation.translate(80, 20);
	window->draw(behindHPBar, transformation);

	hpBar.setSize(Vector2f(250 * (player->StatsManager()->getPlayerHP() / player->StatsManager()->getMaxPlayerHP()), 40));
	window->draw(hpBar, transformation);

	//HP bar text
	displayText.setCharacterSize(24);
	displayText.setString("HP: ");
	transformation.translate(-40, 5);
	window->draw(displayText, transformation);
	displayText.setString(to_string((int)player->StatsManager()->getPlayerHP()) + "/" + to_string((int)player->StatsManager()->getMaxPlayerHP()));
	transformation.translate(300, 0);
	window->draw(displayText, transformation);

	displayText.setCharacterSize(16);

	
	//#END DRAW Player hit points

	//#START DRAW Player status
	ResetTransformation(window->getSize());

	transformation.translate(80, 90);
	displayText.setPosition(0, 0);

	//Hunger bar
	statBar.setSize(Vector2f(150 * (player->StatsManager()->getPlayerHunger() / player->StatsManager()->getPlayerMAXHunger()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Hunger:");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);

	transformation.translate(0, 30);

	//Mood bar	
	statBar.setSize(Vector2f(150 * (player->StatsManager()->getPlayerMood() / player->StatsManager()->getPlayerMAXMood()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Mood:");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);

	transformation.translate(0, 30);

	//Stamina bar	
	statBar.setSize(Vector2f(150 * (player->StatsManager()->getPlayerStamina() / player->StatsManager()->getPlayerMAXStamina()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Stamina: ");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);
	//#END DRAW Player status
}


/*
* <DESCRIPTION>
* Draws the combat options of the player and an arrow at the current choice of the player
*
* @PARAMS
* window: pointer to the game window object.
* currentOption: CombatOptions enum value representing the current combat option the player is considering
*/
void InGameMenuGUI::DrawCombatOptions(RenderWindow *window, CombatOptions *currentOption){

	ResetTransformation(window->getSize());

	transformation.translate(500, 20);

	displayText.setCharacterSize(36);
	for (int i = CombatOptions::First; i <= CombatOptions::Last; ++i){

		displayText.setString(getStringRepCombatOptions(static_cast<CombatOptions>(i)));
		window->draw(displayText, transformation);

		//TODO: add indication arrow of the current option chosen.
		if (*currentOption == static_cast<CombatOptions>(i)){
			transformation.translate(-20, 20);
			window->draw(optionPointerSprite, transformation);
			transformation.translate(20, -20);
		}

		transformation.translate(150, 0);

		//sets values for the next row of options
		if (i == 1){
			transformation.translate(-300, 50);
		}
	}
}


/*
* @RETURNS
* returns a string representation for the CombatOptions enum
*/
string InGameMenuGUI::getStringRepCombatOptions(CombatOptions option){
	switch (option)
	{
		case Attack:
			return "Attack";

		case Spell:
			return "Spell";

		case Item:
			return "Item";

		case Run:
			return "Run";

		default:
			return "No string rep.";
	}
}


/*
* <DESCRIPTION>
* Draws the player inventory and it's items.
*
* @PARAMS
* window: pointer to the game window object.
* player: pointer to the game Player object.
*/
void InGameMenuGUI::DrawPlayerInventory(RenderWindow *window, Player *player){
	ResetTransformation(window->getSize());

	transformation.translate(1060, 15);

	for (int i = 0; i < player->InventoryManager()->getInventoryItems().size(); i++){

		if (i == 3){
			transformation.translate(-270, 90);
		}
		//adds 90 to the x-led pos
		transformation.translate(90, 0);

		window->draw(player->InventoryManager()->getInventoryItems()[i]->getSprite(), transformation);

		//If an item is stackable the amount in the inventory is shown.
		if (player->InventoryManager()->getInventoryItems()[i]->isStackAble()){
			displayText.setString(to_string(player->InventoryManager()->getInventoryItems()[i]->getStackAmount()));
			displayText.setPosition(0, 0);
			transformation.translate(60, 60);

			window->draw(displayText, transformation);

			//resets position for next inventory slot.
			transformation.translate(-60, -60);
		}
	}
}


/*
* <DESCRIPTION>
* Draws the player Action Points. 
* 
* @PARAMS
* window: pointer to the game window object.
* player: pointer to the game Player object.
*/
void InGameMenuGUI::DrawPlayerActionPoints(RenderWindow *window, Player *player){
	ResetTransformation(window->getSize());
	transformation.translate(500, 20);

	for (int i = 0; i < player->StatsManager()->getMaxActionsPoints(); i++){
		if (i + 1 > player->StatsManager()->getRemaningActionPoints()){
			window->draw(player->StatsManager()->getConsumedAPSprite(), transformation);
		}
		else {
			window->draw(player->StatsManager()->getAPSprite(), transformation);
		}

		transformation.translate(30, 0);
	}
}
