#include "GameLoop.h"


/*
* <DESCRIPTION> 
* Constructor for gameloop
*	- sets View and GUIMaster pointers
*	- Initiates all game areas
*	- Initiates the first zone for the player
*
* @PARAMS
*	*gameView: Pointer to the View object for the game.
*	*guiMaster: Pointer to the gui object for the game. (To reduce stack memory)
*	*inGameMenuGUI: pointer to the InGameMenuGUI object.
*	*inputHandler: pointer to the HandleInput object.
*	*_textures: pointer to the TextureLoader object.
*/
GameLoop::GameLoop(View *gameView, GUIMaster *guiMaster, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler, TextureLoader *_textures)
	: view(gameView), gui(guiMaster), gameMenuGUI(inGameMenuGUI), handleInput(inputHandler), textures(_textures)
{
	//A game will allways start in the baseGameArea
	//currentGameArea = baseGameArea;

	baseGameArea = new BaseGameArea(Vector2u(1440, 900), textures);
	survivalGameArea = new SurvivalGameArea(Vector2u(2000, 1500), textures);
	hostileGameArea = new HostileGameArea(Vector2u(2000, 1000), textures);
	finalGameArea = new FinalGameArea(Vector2u(1500, 250), textures);
	currentGameArea = baseGameArea;
	
	lastArea = Base;

	player = new Player(textures);
	player->setAreaPaths(baseGameArea->getAreaPaths());
	player->setBorders(baseGameArea->getAreaSize());
}


GameLoop::~GameLoop()
{
}

/*
* @RETURNS
* returns pointer to the current game area objec.t
*/
IGameArea *GameLoop::getCurrentGameArea(){	
	return currentGameArea;
}

/*
* @RETURNS
* returns pointer to the Player object.
*/
Player* GameLoop::getPlayerPointer(){
	return player;
}

/*
* @RETURNS
* returns a boolean representing if the game is over.
*/
bool GameLoop::GameOver(){
	return isGameOver;
}

/*
* <DESCRIPTION>
* Called whenever a combat phase finishes, 
* resets the game loop timer and removes the VisualEnemy object defeated.
*/
void GameLoop::CombatOver(){
	playerEnteredCombatPhase = false;
	timer.restart();
	getCurrentGameArea()->removeAreaEnemy(currentGameArea->getAreaEnemies()->at(enemyVectorIndex));
	player->StatsManager()->ConsumeActionPoints(1);
}

/*
* @RETURNS
* returns boolean representing if the player has entered combat, true if the player has otherwise false.
*/
bool GameLoop::switchToCombat(){
	return playerEnteredCombatPhase;
}

/*
* @RETURNS
* returns boolean representing if the player has won the game.
*/
bool GameLoop::GameWon(){
	if (currentGameArea->getAreaType() == Areas::Final){
		return currentGameArea->getAreaEnemies()->size() <= 0;
	}
	return false;
}

/*
* @RETURNS
* returns VisualEnemy object the player has engaged.
*/
vector<Enemy*>* GameLoop::getCombatEnemies(){
	return currentGameArea->getAreaEnemies()->at(enemyVectorIndex)->getEnemyGroup();
}

/*
* <DESCRIPTION> 
* Runs the main game outside of combat, calls functions that check
* collisions, if the player has entered a new area, updates positions,
* controls the game "camera" aswell as calling the GUIMaster class to draw the game.
*
* @PARAMS
* *window: pointer to the game window object.
*/
void GameLoop::RunGame(RenderWindow *window){
	//gets timer time
	timeElapsed = timer.getElapsedTime();
	//resets timer instantly after to reuse getElapsedTime to get the time for the loop iteration
	timer.restart();

	//if the newArea is to trigger the final area the game will freeze up
	//to ask the player if he/she wishes to enter the final area.
	if (newArea == Areas::Trigger_Final_Area){
		if (handleInput->CheckEnterKeyPressed()){
			newArea = Areas::Final;
			EnterNewArea(window, view);
		}
		else if (handleInput->CheckBackSpaceKeyPressed()){
			newArea = Areas::No_Area;
			//moves the player back
			//BUGG: This wont work if the path is leading to the east.
			player->setPlayerPosition(Vector2f(player->getPosition().x + 100, player->getPosition().y));
		}
		//if no input is given the freezed game is drawn.
		else {
			gui->DrawGame(currentGameArea->getAreaVisualObjects(), currentGameArea->getAreaEnemies(),window, view, player, triggerdObject, &timeElapsed, amountOfDaysLeft);
			gameMenuGUI->DrawGameMenu(window, player);
			gui->DrawConfirmationBox(window, view, "Are you ready for the final area? Recommended level: 10+");
			return;
		}
	}
		
	//Checks for user input
	newArea = handleInput->CheckUserMovementInput(player, &timeElapsed);
	if (newArea != Areas::No_Area){
		EnterNewArea(window, view);
	}
		
	//If quick menu is active the game must listen for it's keyevent
	if (triggerdObject != NULL){
		//if the key for the quick menu is pressed the object gets triggerd.
		if (handleInput->CheckQuickMenuInput()){
			ExecuteObjectTrigger(window);
		}
	}

	

	triggerdObject = NULL;
	//Checks collisions with each interactable gameobject
	for (unsigned int i = 0; i < currentGameArea->getAreaObjects().size(); ++i){
		//if a player is near an interactable game object a quick menu will be displayed
		if(currentGameArea->getAreaObjects()[i]->isTriggerd(player)){

			triggerdObject = currentGameArea->getAreaObjects()[i];
			break;
		}
	}	

	//Checks for collisions with enemies, if so then combat phase is initiated.
	for (unsigned int i = 0; i < currentGameArea->getAreaEnemies()->size(); ++i){
		if (currentGameArea->getAreaEnemies()->at(i)->collideWithPlayer(player->getSprite().getPosition(), player->getSize())){
			playerEnteredCombatPhase = true;
			enemyVectorIndex = i;
			player->savePosition();
			break;
		}
	}		

	//Camera movement, changes the values of the view to follow the player
	//moves camera X-led
	if (player->getPosition().x >= window->getSize().x / 2 && 
		player->getPosition().x + window->getSize().x/2 <= currentGameArea->getAreaSize().x){

		view->setCenter(player->getPosition().x, view->getCenter().y);
		window->setView(*view);
	}

	//moves camera Y-led
	if (player->getPosition().y + player->getSize().y >= window->getSize().y / 2 &&
		player->getPosition().y + window->getSize().y / 2 - 200 + player->getSize().y <= currentGameArea->getAreaSize().y){

		view->setCenter(view->getCenter().x, player->getPosition().y + player->getSize().y);
		window->setView(*view);
	}

	//draw the game
	gui->DrawGame(currentGameArea->getAreaVisualObjects(), currentGameArea->getAreaEnemies(), window, view, player, triggerdObject, &timeElapsed, amountOfDaysLeft);
	gameMenuGUI->DrawGameMenu(window, player);
}


/*
* <DESCRIPTION> Changes the current game area
*
* @PARAMS
* *window: pointer to the game window object
* *view: pointer to the View object for the game.
*/
void GameLoop::EnterNewArea(RenderWindow *window, View *view){
	switch (newArea)
	{
		case Base:
			currentGameArea = baseGameArea;
			break;
		case Survival:
			currentGameArea = survivalGameArea;
			break;
		case Hostile:
			currentGameArea = hostileGameArea;
			break;

		case Final:
			currentGameArea = finalGameArea;
			break;

			//TODO: <refactor> I don't like to have this enum case as it's technically not an area. 
			//This case is special as it works as a trigger for the final
			//area since the player needs to be questioned if they are prepeared
			//to enter the final area.
		case Trigger_Final_Area:
			return;


		case Dungeon:
			throw "Not implemented yet.";
			break;

		case No_Area:
			throw "Not implemented yet.";
			break;

		default:
			break;
	}

	int y;
	int x = currentGameArea->getAreaSize().x - window->getSize().x / 2;
	if (x < window->getSize().x / 2){
		x = window->getSize().x / 2;
	}

	if (currentGameArea->getAreaType() != Areas::Final){
		for (unsigned int i = 0; i < currentGameArea->getAreaPaths().size(); ++i){
			//gets the path that leads back to the last area to set the player position.
			if (currentGameArea->getAreaPaths()[i]->getNextArea() == lastArea){
				player->setPlayerPosition(currentGameArea->getAreaPaths()[i]->getPosition());
				lastArea = newArea;

				y = currentGameArea->getAreaPaths()[i]->getPosition().y + currentGameArea->getAreaPaths()[i]->getSize().y / 2;

				if (currentGameArea->getAreaPaths()[i]->getPosition().x == 0){
					x = window->getSize().x / 2;
				}
				break;
			}
		}
	}
	//TODO: fix this temp solution due to final area has no path back.
	else{
		player->setPlayerPosition(Vector2f(currentGameArea->getAreaSize().x - 100, currentGameArea->getAreaSize().y / 2 - 15));	
		x = currentGameArea->getAreaSize().x - window->getSize().x / 2;
		y = 200;
		
	}
	
	player->setAreaPaths(currentGameArea->getAreaPaths());
	player->setBorders(currentGameArea->getAreaSize());
	
	
	view->setCenter(x, y);
	window->setView(*view);
}






/*
* <DESCRIPTION>
* Called when a game object was triggerd, depending on the game objects trigger type diffrent 
* functions and actions will be taken.
*
* @PARAMS
* *window: pointer to the game window object
*/
void GameLoop::ExecuteObjectTrigger(RenderWindow *window){

	switch (triggerdObject->getTriggerType()){

		case TriggerType::Harvest:
		case TriggerType::Loot:
			if (player->StatsManager()->getRemaningActionPoints() > 0){
				player->InventoryManager()->addItem(new GameItem(triggerdObject->getObjectType(), textures));
				//TODO: dont remove object if it's not looted
				currentGameArea->removeAreaObject(triggerdObject);
				player->StatsManager()->ConsumeActionPoints(1);
			}
			else {
				gui->AddGameAlert("You do not have sufficient Action Points.", player->getPosition() + Vector2f(player->getSize().x, 0));
			}		
			break;

		case TriggerType::Build: 
			if (player->StatsManager()->getRemaningActionPoints() > 0){
				triggerdObject->MaterialListManager()->addItemsToConstruction(player);

				if (triggerdObject->MaterialListManager()->getMaterialList().size() <= 0){
					triggerdObject->completeConstruction();
				}
			}
			else {
				gui->AddGameAlert("You do not have sufficient Action Points.", player->getPosition() + Vector2f(player->getSize().x, 0));
			}
			break;


		case TriggerType::Interactable:
			switch (triggerdObject->getObjectType())
			{
				case GameObjectType::Bed:	
					amountOfDaysLeft -= 1;

					gui->activateSleepAnimation(Vector2f(window->getSize().x, window->getSize().y), baseGameArea->playerHasBurningFirePlace());
					handleInput->DisableControls(gui->getSleepAnimationTime());
					player->Sleep(baseGameArea->playerHasBurningFirePlace());

					
								
					//TODO: give the player a notice on the last day to warn them that the game is about to be over.
					
					hostileGameArea->RespawnEnemies(amountOfDaysLeft);
					survivalGameArea->RespawnResources(amountOfDaysLeft);

					//burns out a fireplace if one is active.
					if (baseGameArea->playerHasBurningFirePlace()){
						baseGameArea->firePlaceBurnOut();
					}

					//if the player has no HP left the game is over 
					if (player->StatsManager()->getPlayerHP() <= 0){
						isGameOver = true;
					}
					//if there is 0 days left then the game is over.
					if (amountOfDaysLeft <= 0){
						isGameOver = true;
					}
					break; 

				default:
					throw "Object type is not interactable.";
					break;
			}
			break;

		case TriggerType::Usable:
			switch (triggerdObject->getObjectType())
			{
				case HealingStation:
					//if the player al�ready has full health there is no use of using the healing station
					if (player->StatsManager()->getPlayerHP() == player->StatsManager()->getMaxPlayerHP()){
						gui->AddGameAlert("You already have full health.", player->getPosition() + Vector2f(player->getSize().x, 0));
						break;
					}

					
					if (player->StatsManager()->getRemaningActionPoints() > 0){
						if (player->InventoryManager()->PlayerHasItem(triggerdObject->getConsumptionType())){

							player->InventoryManager()->ConsumeInventoryItem(triggerdObject->getConsumptionType());
							player->StatsManager()->playerHitPointsAffected(player->StatsManager()->getMaxPlayerHP() * .1);
							player->StatsManager()->ConsumeActionPoints(1);
						}
						else {
							gui->AddGameAlert("You do not have the required resources to use this.", player->getPosition() + Vector2f(player->getSize().x, 0));
						}
					}
					else {
						gui->AddGameAlert("You do not have sufficient Action Points.", player->getPosition() + Vector2f(player->getSize().x, 0));
					}

					break;

				default:
					throw "Object is not useable.";
					break;
			}

			break;


		case TriggerType::Set_On_Fire:
			if (player->SkillManager()->hasPlayerLearnedFireball() &&
				player->SkillManager()->canSetObjectOnFire()){

				triggerdObject->setOnFire();
			}
			else{
				gui->AddGameAlert("You have not yet learned the skill Hadouk...I mean Fireball.", player->getPosition() + Vector2f(player->getSize().x, 0));
			}
			break;

		case TriggerType::No_Action:
			//Nothing happens
			break;

		default:
			throw "Default case should not be reachable. Object has no trigger type.";
			break;
	}
}