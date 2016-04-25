#include "HandleInput.h"

HandleInput::HandleInput()
{
}


HandleInput::~HandleInput()
{
}




int HandleInput::CheckTargetChoiceInput(Time t, int currentIndex, int maxIndex){
	if (controlsEnabled){
		if (Keyboard::isKeyPressed(Keyboard::W)){
			if (currentIndex == 0 && maxIndex > 1){				
				DisableControls(.25);
				return currentIndex + 1;
			}
			else if (maxIndex == 3 && currentIndex + 1 == maxIndex){
				DisableControls(.25);
				return currentIndex - 2;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)){
			if (currentIndex - 1 == 0){				
				DisableControls(.25);
				return currentIndex - 1;
			}
			else if (currentIndex == 0 && maxIndex == 3){
				DisableControls(.25);
				return currentIndex + 2;
			}
		}
	}
	else{
		updatePauseTimer(t.asSeconds());
	}
	
	return currentIndex;
}






bool HandleInput::CheckUserCombatDecision(){
	if (Keyboard::isKeyPressed(Keyboard::Return)){
		return true;
	}
	return false;
}



CombatOptions HandleInput::CheckUserCombatInput(CombatOptions currentOption){

	if (Keyboard::isKeyPressed(Keyboard::W)){
		if (currentOption - 2 >= CombatOptions::First &&
			currentOption - 2 <= CombatOptions::Last){

			currentOption = static_cast<CombatOptions>(currentOption - 2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)){
		if (currentOption + 2 >= CombatOptions::First &&
			currentOption + 2 <= CombatOptions::Last){

			currentOption = static_cast<CombatOptions>(currentOption + 2);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A)){
		if ((currentOption - 1) %2 == 0){
			currentOption = static_cast<CombatOptions>(currentOption - 1);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)){
		if ((currentOption + 1) % 2 == 1){
			currentOption = static_cast<CombatOptions>(currentOption + 1);
		}
	}

	return currentOption;
}

/*
* <DESCRIPTION>
* Checks for user input and executes the proper order
*
* @PARAMS
* Player *player: pointer to the Player object
*
* @RETURNS
* returns an Enum Value of Areas representing any newly entered area.
*/
//TODO: Rename to CheckUserMovementInput
Areas HandleInput::CheckUserMovementInput(Player *player, Time *t){

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