#pragma once
#include "CombatGUI.h"
#include "InGameMenuGUI.h"
#include "HandleInput.h"


class GameCombatLoop
{
public:
	GameCombatLoop(View *gameView, Player *p, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler);
	~GameCombatLoop();
	void runCombatLoop(RenderWindow *window, vector<Enemy*> *enemies);
	void InitiateCombatLoopValues();
	bool isNormalRenderingActive();
	bool IsCombatOver();

private:
	HandleInput *handleInput;
	InGameMenuGUI *combatMenuGUI;
	bool phaseTransmissionAnimation = true;
	View *view;
	CombatGUI *gui = NULL;
	Player *player;
	Time timeElapsed;
	Clock timer;
	CombatOptions currentOption;
	int targetIndex = 0;
	CombatState currentCombatState = CombatState::Choosing_Action;

	int currentEnemyTurnIndex = 0;
	bool attackConfirm = false;
	const float enemyTurnTime = 2;
	float currentEnemyTurnTime = 0;
	void NewEnemyTurn();

	void ExecuteCombatOption();
};

