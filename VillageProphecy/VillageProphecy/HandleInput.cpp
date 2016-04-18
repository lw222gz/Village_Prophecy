#include "HandleInput.h"

HandleInput::HandleInput()
{
}


HandleInput::~HandleInput()
{
}


Areas HandleInput::CheckUserInput(Player *player, Time *t){

	area = Areas::No_Area;

	if (controlsEnabled){
		if (Keyboard::isKeyPressed(Keyboard::W)){
			area = player->playerMove(MoveDirection::Up, t);
		}

		else if (Keyboard::isKeyPressed(Keyboard::S)){
			area = player->playerMove(MoveDirection::Down, t);
		}

		else if (Keyboard::isKeyPressed(Keyboard::A)){
			area = player->playerMove(MoveDirection::Left, t);
		}

		else if (Keyboard::isKeyPressed(Keyboard::D)){
			area = player->playerMove(MoveDirection::Right, t);
		}
	}
	else{
		updatePauseTimer(t->asSeconds());
	}
	

	return area;
}


bool HandleInput::checkQuickMenuInput(){
	if (controlsEnabled && Keyboard::isKeyPressed(Keyboard::R)){
		return true;
	}
	return false;
}


void HandleInput::DisableControls(float secondsToPause){
	controlsEnabled = false;
	pauseTime = secondsToPause;
	currentPauseTime = 0;
}

void HandleInput::updatePauseTimer(float passedSeconds){
	currentPauseTime += passedSeconds;
	if (currentPauseTime / pauseTime >= 1){
		controlsEnabled = true;
	}
}