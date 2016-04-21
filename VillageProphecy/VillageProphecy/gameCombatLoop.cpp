#include "GameCombatLoop.h"

GameCombatLoop::GameCombatLoop(View *gameView, Player *p)
	: view(gameView), player(p)
{
	gui = new CombatGUI(view);
}


GameCombatLoop::~GameCombatLoop()
{

}

void GameCombatLoop::InitiateCombatLoopValues(){
	timer.restart();
	phaseTransmissionAnimation = true;
	player->setPlayerPosition(Vector2f(view->getCenter().x - 400,
		view->getCenter().y - player->getSize().y));
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
		gui->DrawCombatPhase(window, &timeElapsed, player);
	}

	if (phaseTransmissionAnimation){
		gui->TransitionAnimation(window, &timeElapsed);
		if (gui->isTransitionAnimationOver()){
			phaseTransmissionAnimation = false;
			gui->ResetAnimationValues();
		}
	}

	

}