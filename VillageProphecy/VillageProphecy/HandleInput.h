#pragma once
#include "Player.h"
//#include "MoveDirection.h"
//#include "GameAreas.h"
//#include <SFML/Graphics.hpp>

using namespace sf;

class HandleInput
{
public:
	HandleInput();
	~HandleInput();
	Areas CheckUserInput(Player *player, Time *t);
	void DisableControls(float secondsToPause);
	bool checkQuickMenuInput();

private:
	Areas area = Areas::No_Area;
	bool controlsEnabled = true;
	float pauseTime = 0;
	float currentPauseTime = 0;

	void updatePauseTimer(float passedSeconds);
};

