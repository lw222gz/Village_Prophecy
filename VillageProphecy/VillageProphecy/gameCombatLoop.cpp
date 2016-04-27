#include "GameCombatLoop.h"

GameCombatLoop::GameCombatLoop(View *gameView, Player *p, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler)
	: view(gameView), player(p), combatMenuGUI(inGameMenuGUI), handleInput(inputHandler)
{
	gui = new CombatGUI(view);
}


GameCombatLoop::~GameCombatLoop()
{
}

/*
* @RETURNS
* returns boolean, true if the fight is over, otherwise false.
*/
bool GameCombatLoop::IsCombatOver(){
	return (currentCombatState == CombatState::Combat_Phase_Over);
}


bool GameCombatLoop::IsGameOver(){
	return (currentCombatState == CombatState::Game_Over);
}




/*
* <DESCRIPTION>
* Since there will be several diffrent enemy encounters this metod will reset some values required
* each time a new battle is initiated.
*/
void GameCombatLoop::InitiateCombatLoopValues(){
	timer.restart();
	phaseTransmissionAnimation = true;
	gui->ResetTransitionAnimationValues();
	player->setPlayerPosition(Vector2f(320, 330));
	currentOption = CombatOptions::Attack;
	currentCombatState = CombatState::Choosing_Action;
	targetIndex = 0;
	currentEnemyTurnIndex = 0;
	currentEnemyTurnTime = 0;
	phaseSwitchPause = 0;
	gui->ResetMessages();
	hasDisplayedPlayerDied = false;	
}

/*
* <DESCRIPTION>
* Then this method returns true, the game will start to clear the screen each iteration of the game loop.
*
* @RETURNS
* returns true if normal rendering of the combat phase is active
*/
bool GameCombatLoop::isNormalRenderingActive(){
	return gui->isNormalRenderingActive();
}

/*
* <DESCRIPTION>
* Game loop for the combat phase of the game.
* Calls gui methods and controls the combat phase between the player and the enemies he/she faces.
*
* @PARAMS
* window: pointer to the game window object.
* enemies: pointer to a vector of enemies the player is facing. 
*/
//TODO: add possibilty to go back to previous options during combat
void GameCombatLoop::runCombatLoop(RenderWindow *window, vector<Enemy*> *enemies){

	//gets timer time
	timeElapsed = timer.getElapsedTime();
	//resets timer instantly after to reuse getElapsedTime to get the time for the loop iteration
	timer.restart();

	if (isNormalRenderingActive()){
		switch (currentCombatState)
		{
			case Choosing_Action:
				currentOption = handleInput->CheckUserCombatInput(currentOption);
				if (handleInput->CheckUserCombatDecision()){
					ExecuteCombatOption();
				}
				break;

			case Choosing_Target:
				targetIndex = handleInput->CheckTargetChoiceInput(timeElapsed, targetIndex, enemies);
				gui->DrawTargetArrow(window, targetIndex);

				if (handleInput->CheckUserCombatDecision()){

					currentCombatState = CombatState::Enemy_Turn;
					currentEnemyTurnTime = 0;

					enemies->at(targetIndex)->TakeDamage(player->StatsManager()->getPlayerAttackDamage());
					gui->AddCombatText(to_string((int)player->StatsManager()->getPlayerAttackDamage()), targetIndex);

					//If the enemy died a new target index is set.
					if (!enemies->at(targetIndex)->IsAlive()){

						for (int i = 0; i < enemies->size(); ++i){
							if (enemies->at(i)->IsAlive()){
								targetIndex = i;
								break;
							}
							//Last iteration of the loop.
							if (i + 1 == enemies->size()){
								//All enemies are dead and the normal gameplay should resume.
								//TODO: add player XP
								currentCombatState = CombatState::Combat_Over;
								gui->AddStatusText("You Won!");

								//grants the player wind EXP
								for (auto &e : *enemies){
									player->StatsManager()->GainEXPPoints(e->getXPGrant());
								}
							}
						}
					}
					
				}
				
				break;

			//Runs all enemy turns, when all enemies have executed their actions then 
			//it goes back to the players turn.
			case Enemy_Turn:
				//If all enemies have had their turns then it goes back to the player
				if (currentEnemyTurnIndex >= enemies->size()){
					currentCombatState = Choosing_Action;		
					gui->AddStatusText("Your move!");
					NewEnemyTurn();
					currentEnemyTurnIndex = 0;
					break;
				}

				if (enemies->at(currentEnemyTurnIndex)->IsAlive()){
					if (attackConfirm){
						currentEnemyTurnTime += timeElapsed.asSeconds();
						gui->DrawEnemyAttackAnimation(enemies->at(currentEnemyTurnIndex), currentEnemyTurnTime, enemyTurnTime);

						if (currentEnemyTurnTime >= enemyTurnTime){
							NewEnemyTurn();
						}
					}
					else if(!attackConfirm) {
						player->StatsManager()->damagePlayer(enemies->at(currentEnemyTurnIndex)->getAttackDamage());
						gui->AddPlayerCombatText(to_string((int)enemies->at(currentEnemyTurnIndex)->getAttackDamage()), player);
						gui->AddStatusCombatText(enemies->at(currentEnemyTurnIndex)->getEnemyType());
						attackConfirm = true;

						if (player->StatsManager()->getPlayerHP() <= 0){
							currentCombatState = Player_Lost;
						}
					}

				}
				else {					
					NewEnemyTurn();
				}

				
				break;

			case Combat_Over: 
				phaseSwitchPause += timeElapsed.asSeconds();
				if (phaseSwitchPause >= phaseSwitchPauseTime){
					currentCombatState = Combat_Phase_Over;
				}
				//after 1 sec switch back to normal game mode
				break;

			case Player_Lost:
				phaseSwitchPause += timeElapsed.asSeconds();

				//TODO: -optimize- hasDisplayedPlayerDied is a quick fix.
				if (!hasDisplayedPlayerDied && phaseSwitchPause >= .5){
					gui->AddStatusText("You died.");
					hasDisplayedPlayerDied = true;
				}
				if (phaseSwitchPause >= phaseSwitchPauseTime + .5){
					currentCombatState = Game_Over;					
				}
				break;

			default:
				break;
		}
		
		
		gui->DrawCombatPhase(window, &timeElapsed, player, enemies);
		combatMenuGUI->DrawCombatMenu(window, player, &currentOption);
		gui->DrawCombatText(window, &timeElapsed);		
	}

	if (phaseTransmissionAnimation){
		gui->TransitionAnimation(window, &timeElapsed);
		if (gui->isTransitionAnimationOver()){
			phaseTransmissionAnimation = false;			
		}
	}
}

/*
* <DESCRIPTION>
* Sets values for a new enemy to take it's turn.
*/
void GameCombatLoop::NewEnemyTurn(){
	currentEnemyTurnIndex += 1;
	currentEnemyTurnTime = 0;
	attackConfirm = false;
}


/*
* <DESCRIPTION>
* Executes a combat option the player decided on doing.
*/
void GameCombatLoop::ExecuteCombatOption(){
	switch (currentOption)
	{
		case CombatOptions::Attack:
			currentCombatState = CombatState::Choosing_Target;
			break;

		case CombatOptions::Spell:
			gui->AddStatusText("You dont know any spells yet.");
			break;

		case CombatOptions::Item:
			gui->AddStatusText("Not Implemented Yet.");
			break;

		case CombatOptions::Run:
			gui->AddStatusText("Not Implemented Yet.");
			break;


		default:
			throw "Not a valid combat option was executed.";
			break;
	}
}