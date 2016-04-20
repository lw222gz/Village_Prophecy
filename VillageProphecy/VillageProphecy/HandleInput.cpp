#include "HandleInput.h"

HandleInput::HandleInput()
{
}


HandleInput::~HandleInput()
{
}

/*
* <DESCRIPTION>
* Checks for user input and executes the proper order
*
* @PARAMS
* Player *player: 
*
* @RETURNS
*
*/
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

/*
* <DESCRIPTION>
* Checks for quick menu bind (R key) 
*
* @RETURNS
* returns boolean, true if the player has pressed the R-key, otherwise false.
*/
bool HandleInput::checkQuickMenuInput(){
	if (controlsEnabled && Keyboard::isKeyPressed(Keyboard::R)){
		return true;
	}
	return false;
}

/*
* <DESCRIPTION>
* Disables the player controls for X amount of seconds
*
* @PARAMS
* secondsToPause: float representing the amount of seconds the player wont be abel to use the controls.
*/
void HandleInput::DisableControls(float secondsToPause){
	controlsEnabled = false;
	pauseTime = secondsToPause;
	currentPauseTime = 0;
}

/*
* <DESCRIPTION>
* If the controls are disabled this method is called. It will update the pause timer.
*
* @PARAMS
* passedSeconds: float representing the amount of seconds that has passed this loop iteration
*/
void HandleInput::updatePauseTimer(float passedSeconds){
	currentPauseTime += passedSeconds;
	if (currentPauseTime / pauseTime >= 1){
		controlsEnabled = true;
	}
}