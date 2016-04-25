#include "GameCombatLoop.h"

GameCombatLoop::GameCombatLoop(View *gameView, Player *p, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler)
	: view(gameView), player(p), combatMenuGUI(inGameMenuGUI), handleInput(inputHandler)
{
	gui = new CombatGUI(view);
}


GameCombatLoop::~GameCombatLoop()
{
}

//returns true if the combat phase is over.
bool GameCombatLoop::IsCombatOver(){
	return (currentCombatState == CombatState::Combat_Over);
}

void GameCombatLoop::InitiateCombatLoopValues(){
	timer.restart();
	phaseTransmissionAnimation = true;
	gui->ResetAnimationValues();
	player->setPlayerPosition(Vector2f(view->getCenter().x - 400,
										view->getCenter().y - player->getSize().y));
	currentOption = CombatOptions::Attack;
	currentCombatState = CombatState::Choosing_Action;
	targetIndex = 0;
	
}


bool GameCombatLoop::isNormalRenderingActive(){
	return gui->isNormalRenderingActive();
}


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

					enemies->at(targetIndex)->TakeDamage(10);
					gui->AddCombatText("10" , targetIndex);

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
								currentCombatState = CombatState::Combat_Over;
							}
						}
					}
					
				}
				
				break;

			case Enemy_Turn:
				currentCombatState = Choosing_Action;
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


void GameCombatLoop::ExecuteCombatOption(){
	switch (currentOption)
	{
		case CombatOptions::Attack:
			currentCombatState = CombatState::Choosing_Target;
			break;

		case CombatOptions::Spell:
			break;

		case CombatOptions::Item:
			break;

		case CombatOptions::Run:
			break;


		default:
			throw "Not a valid combat option was executed.";
			break;
	}
}