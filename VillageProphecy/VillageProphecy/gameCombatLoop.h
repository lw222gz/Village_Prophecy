#pragma once
#include "CombatGUI.h"
#include "InGameMenuGUI.h"
#include "HandleInput.h"
#include "EnemySkill.h"
#include <math.h>
#include <stdio.h>
#include <cstdio>

class GameCombatLoop
{
public:
	GameCombatLoop(View *gameView, Player *p, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler);
	~GameCombatLoop();
	void runCombatLoop(RenderWindow *window, vector<Enemy*> *enemies);
	void InitiateCombatLoopValues();
	bool isNormalRenderingActive();
	bool IsCombatOver();
	bool IsGameOver();

private:
	HandleInput *handleInput;
	InGameMenuGUI *combatMenuGUI;
	View *view;
	CombatGUI *gui = NULL;
	Player *player;
	Time timeElapsed;
	Clock timer;
	CombatOptions currentOption;	
	CombatState currentCombatState = CombatState::Choosing_Action;
	bool phaseTransmissionAnimation = true;

	int targetIndex = 0;
	int skillChoiceIndex = 0;
	int currentEnemyTurnIndex = 0;
	bool attackConfirm = false;
	const float enemyTurnTime = 2;
	float currentEnemyTurnTime = 0;

	float phaseSwitchPause = 0;
	const float phaseSwitchPauseTime = 1;
	bool hasDisplayedPlayerDied = false;

	void NewEnemyTurn();
	void ExecuteCombatOption();
	void ExecuteSkillOption();
	void ExecuteRandomEnemySkill(Enemy* enemy);
	void ExecuteEnemySkillEffect(SkillEffect skillEffect);
	void PlayerCanGoBack();
	void PlayerDealsDamage(vector<Enemy*> *enemies, int damage);
	void PlayerTakesDamage(int amount, EnemyType enemyType, string attackName);

	float debuffTickTimer = 0;
	int debuffTickIndex = 0;
	bool debuffPhaseOver = false;
	struct Debuff
	{
		SkillEffect effect;
		int roundsToLast;		
		string name;
	};
	//A vector of all the debuffs of the current battle.
	vector<Debuff> playerDebuffs;
	//vector<SkillEffect*> enemyDebuffs;
};

