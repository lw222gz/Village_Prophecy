#include "HandleInput.h"

HandleInput::HandleInput()
{
}


HandleInput::~HandleInput()
{
}


Areas HandleInput::CheckUserInput(Player *player, Time *t){

	area = Areas::No_Area;

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

	return area;
}


bool HandleInput::checkQuickMenuInput(){
	if (Keyboard::isKeyPressed(Keyboard::R)){
		return true;
	}
	return false;
}
