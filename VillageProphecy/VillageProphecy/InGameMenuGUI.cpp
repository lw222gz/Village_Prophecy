#include "InGameMenuGUI.h"


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
}


InGameMenuGUI::~InGameMenuGUI()
{
}


void InGameMenuGUI::DrawGameMenu(RenderWindow *window, Player *player){
	DrawBaseMenu(window);

	DrawPlayerInventory(window, player);

	DrawPlayerActionPoints(window, player);

	DrawPlayerStats(window, player);
}

void InGameMenuGUI::DrawCombatMenu(RenderWindow *window, Player *player, CombatOptions *currentOption){
	DrawBaseMenu(window);

	DrawPlayerInventory(window, player);
	
	DrawPlayerStats(window, player);

	DrawCombatOptions(window, currentOption);
}

void InGameMenuGUI::ResetTransformation(){
	transformation.translate(-transformation.transformPoint(0, 0));
}

void InGameMenuGUI::DrawBaseMenu(RenderWindow *window){
	inGameMenuSprite.setPosition(view->getCenter().x - window->getSize().x / 2,
		view->getCenter().y + window->getSize().y / 2 - 200);
	window->draw(inGameMenuSprite);
}



void InGameMenuGUI::DrawPlayerStats(RenderWindow *window, Player *player){
	//#START DRAW Player hit points
	transformation.translate(inGameMenuSprite.getPosition().x + 80, inGameMenuSprite.getPosition().y + 20);
	window->draw(behindHPBar, transformation);

	hpBar.setSize(Vector2f(250 * (player->getPlayerHP() / player->getMaxPlayerHP()), 40));
	window->draw(hpBar, transformation);

	//HP bar text
	displayText.setCharacterSize(24);
	displayText.setString("HP: ");
	transformation.translate(-40, 5);
	window->draw(displayText, transformation);
	displayText.setString(to_string((int)player->getPlayerHP()) + "/" + to_string((int)player->getMaxPlayerHP()));
	transformation.translate(300, 0);
	window->draw(displayText, transformation);

	displayText.setCharacterSize(16);

	ResetTransformation();
	//#END DRAW Player hit points

	//#START DRAW Player status
	transformation.translate(inGameMenuSprite.getPosition().x + 80, inGameMenuSprite.getPosition().y + 90);
	displayText.setPosition(0, 0);

	//Hunger bar
	statBar.setSize(Vector2f(150 * (player->getPlayerHunger() / player->getPlayerMAXHunger()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Hunger:");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);

	transformation.translate(0, 30);

	//Mood bar	
	statBar.setSize(Vector2f(150 * (player->getPlayerMood() / player->getPlayerMAXMood()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Mood: ");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);

	transformation.translate(0, 30);

	//Stamina bar	
	statBar.setSize(Vector2f(150 * (player->getPlayerStamina() / player->getPlayerMAXStamina()), 10));
	window->draw(behindStatBar, transformation);
	window->draw(statBar, transformation);

	displayText.setString("Stamina: ");
	transformation.translate(-70, -6);
	window->draw(displayText, transformation);
	transformation.translate(70, 6);
	//#END DRAW Player status

	ResetTransformation();
}



void InGameMenuGUI::DrawCombatOptions(RenderWindow *window, CombatOptions *currentOption){
	transformation.translate(inGameMenuSprite.getPosition().x + 500, inGameMenuSprite.getPosition().y + 20);

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
		if (i == 1){
			transformation.translate(-300, 50);
		}
	}

	ResetTransformation();
}

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



void InGameMenuGUI::DrawPlayerInventory(RenderWindow *window, Player *player){
	transformation.translate(inGameMenuSprite.getPosition().x + 1060, inGameMenuSprite.getPosition().y + 15);

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
	ResetTransformation();
}

void InGameMenuGUI::DrawPlayerActionPoints(RenderWindow *window, Player *player){
	transformation.translate(inGameMenuSprite.getPosition().x + 500, inGameMenuSprite.getPosition().y + 20);

	//trans.translate(100, 100);
	for (int i = 0; i < player->getMaxActionsPoints(); i++){
		if (i + 1 > player->getRemaningActionPoints()){
			window->draw(player->getConsumedAPSprite(), transformation);
		}
		else {
			window->draw(player->getAPSprite(), transformation);
		}

		transformation.translate(30, 0);
	}

	ResetTransformation();
}
