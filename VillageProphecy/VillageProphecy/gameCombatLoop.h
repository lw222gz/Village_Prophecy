#pragma once
#include "CombatGUI.h"
#include "Enemy.h"

class GameCombatLoop
{
public:
	GameCombatLoop(View *gameView, Player *p);
	~GameCombatLoop();
	void runCombatLoop(RenderWindow *window, vector<Enemy*> *enemies);
	void InitiateCombatLoopValues();
	bool isNormalRenderingActive();

private:
	bool phaseTransmissionAnimation = true;
	View *view;
	CombatGUI *gui = NULL;
	Player *player;
	Time timeElapsed;
	Clock timer;
};

