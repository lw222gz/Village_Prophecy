#include "GameLoop.h"

GameLoop::GameLoop(View *gameView, GUIMaster *guiMaster) : view(gameView), gui(guiMaster){

	survivalGameArea = new GameArea(Areas::Survival, Vector2u(3000, 1500));
	hostileGameArea = new GameArea(Areas::Hostile, Vector2u(4000, 1000));
	baseGameArea = new GameArea(Areas::Base, Vector2u(1440, 900));

	//A game will allways start in the baseGameArea
	currentGameArea = baseGameArea;
	lastArea = Areas::Base;
	player.setAreaPaths(currentGameArea->getAreaPaths());
	player.setBorders(currentGameArea->getAreaSize());
}


GameLoop::~GameLoop()
{
}

//returns boolean representing if game is over.
bool GameLoop::GameOver(){
	return isGameOver;
}

void GameLoop::RunGame(RenderWindow *window){

	//gets timer time
	timeElapsed = timer.getElapsedTime();
	//resets timer instantly after to reuse getElapsedTime to get the time for the loop iteration
	timer.restart();
		
	//Checks for user input
	newArea = handleInput.CheckUserInput(&player, &timeElapsed);
	if (newArea != Areas::No_Area){
		EnterNewArea(window, view);
	}
		
	//If quick menu is active the game must listen for it's keyevent
	if (triggerdObject != NULL){
		//if the key for the quick menu is pressed the object gets triggerd.
		if (handleInput.checkQuickMenuInput()){
			ExecuteObjectTrigger(window);
		}
	}

	

	triggerdObject = NULL;
	//Checks collisions with each interactable gameobject
	for (int i = 0; i < currentGameArea->getAreaObjects().size(); ++i){
		//if a player is near an interactable game object a quick menu will be displayed
		if(currentGameArea->getAreaObjects()[i]->isTriggerd(&player)){
			triggerdObject = currentGameArea->getAreaObjects()[i];
			//gui.setQuickMenu(currentGameArea->getAreaObjects()[i]);
			break;
		}
	}	

	//TEST CODE!
	if (lastArea == Areas::Survival){
		Texture test;
		if (!test.loadFromFile("Textures/PHTest.png")){
			throw "Test img did not load correctly.";
		}
		Sprite s;
		s.setTexture(test);
		s.setPosition(Vector2f(1200, 100));

		window->draw(s);

		s.setPosition(Vector2f(2800, 100));
		window->draw(s);
	}
	//END TEST CODE

		

	//Camera movement, changes the values of the view to follow the player
	//moves camera X-led
	if (player.getPosition().x >= window->getSize().x / 2 && 
		player.getPosition().x + window->getSize().x/2 <= currentGameArea->getAreaSize().x){

		view->setCenter((window->getSize().x / 2) + (player.getPosition().x - window->getSize().x / 2), view->getCenter().y);
		window->setView(*view);
	}
	//moves camera Y-led
	if (player.getPosition().y + player.getSize().y >= window->getSize().y / 2 &&
		player.getPosition().y + window->getSize().y / 2 - 200 + player.getSize().y <= currentGameArea->getAreaSize().y){

		view->setCenter(view->getCenter().x, player.getPosition().y + player.getSize().y);
		window->setView(*view);
	}

	//draw the game
	gui->DrawGame(currentGameArea->getAreaVisualObjects(), window, view, &player, triggerdObject, &timeElapsed, amountOfDaysLeft);
}

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
	//TODO: write cases
	case Dungeon:
		break;
	case Final:
		break;
	case No_Area:
		break;
	default:
		break;
	}

	int y;
	int x = currentGameArea->getAreaSize().x - window->getSize().x / 2;
	if (x < window->getSize().x / 2){
		x = window->getSize().x / 2;
	}
	for (unsigned int i = 0; i < currentGameArea->getAreaPaths().size(); ++i){
		//gets the path that leads back to the last area to set the player position.
		if (currentGameArea->getAreaPaths()[i]->getNextArea() == lastArea){
			player.setPlayerPosition(currentGameArea->getAreaPaths()[i]->getPosition());
			lastArea = newArea;

			y = currentGameArea->getAreaPaths()[i]->getPosition().y + currentGameArea->getAreaPaths()[i]->getSize().y / 2;

			if (currentGameArea->getAreaPaths()[i]->getPosition().x == 0){
				x = window->getSize().x / 2;
			}
			break;
		}
	}
	player.setAreaPaths(currentGameArea->getAreaPaths());
	player.setBorders(currentGameArea->getAreaSize());
	
	
	view->setCenter(x, y);
	window->setView(*view);
}







void GameLoop::ExecuteObjectTrigger(RenderWindow *window){

	switch (triggerdObject->getTriggerType()){

		case TriggerType::Harvest:
		case TriggerType::Loot:
			player.InventoryManager()->addItem(new GameItem(triggerdObject->getObjectType()));
			//TODO: dont remove object if it's not looted
			currentGameArea->removeAreaObject(triggerdObject);
			break;

		case TriggerType::Build: 
			triggerdObject->MaterialListManager()->addItemsToConstruction(player.InventoryManager());

			if (triggerdObject->MaterialListManager()->getMaterialList().size() <= 0){
				triggerdObject->completeConstruction();
			}
			//TODO: build trigger for construction
			break;


		case TriggerType::Interactable:
			switch (triggerdObject->getObjectType())
			{
			case GameObjectType::Bed:				
				gui->activateSleepAnimation(Vector2f(window->getSize().x, window->getSize().y));
				handleInput.DisableControls(gui->getSleepAnimationTime());
				player.Sleep();
				amountOfDaysLeft -= 1;
				//TODO: give the player a notice on the last day to warn them that the game is about to be over.

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
		case TriggerType::No_Action:
			//Nothing happens
			break;

		default:
			throw "Default case should not be reachable. Object has no trigger type.";
			break;
	}
}