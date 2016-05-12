#pragma once
#include "Player.h"
#include "CombatOptions.h"
#include "Enemy.h"

using namespace sf;

class HandleInput
{
public:
	HandleInput();
	~HandleInput();
	Areas CheckUserMovementInput(Player *player, Time *t);
	CombatOptions CheckUserCombatInput(CombatOptions currentOption);
	int CheckTargetChoiceInput(Time t, int currentIndex, vector<Enemy*> *enemies);
	int CheckSkillChoiceInput(Time *t, int currentIndex, int maxIndex);
	bool CheckEnterKeyPressed();
	bool CheckBackSpaceKeyPressed();
	void DisableControls(float secondsToPause);
	bool CheckQuickMenuInput();
	bool CheckResetCombatStateInput();

private:
	Areas area = Areas::No_Area;
	bool controlsEnabled = true;
	bool enterJustPressed = false;
	bool rKeyJustPressed = false;
	float pauseTime = 0;
	float currentPauseTime = 0;

	void updatePauseTimer(float passedSeconds);
};

