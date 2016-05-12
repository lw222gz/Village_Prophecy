#pragma once
#include "Player.h"
#include "HandleInput.h"
#include "GUIMaster.h"
#include "InGameMenuGUI.h"
#include "GameAreas.h"

#include "SurvivalGameArea.h"
#include "HostileGameArea.h"
#include "FinalGameArea.h"
#include "BaseGameArea.h"
#include "IGameArea.h"

using namespace sf;
using namespace std;

class IGameArea;
class BaseGameArea;
class SurvivalGameArea;
class HostileGameArea;
class FinalGameArea;


class GameLoop
{
public:
	GameLoop(View *view, GUIMaster *gui, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler);
	~GameLoop();
	void RunGame(RenderWindow *window);
	bool GameOver();
	bool GameWon();
	bool switchToCombat();
	Player* getPlayerPointer();
	vector<Enemy*>* getCombatEnemies();
	void CombatOver();

	IGameArea *getCurrentGameArea();

	

private:
	InGameMenuGUI *gameMenuGUI;
	bool playerEnteredCombatPhase = false;
	int enemyVectorIndex = 0;
	bool isGameOver = false;
	Time timeElapsed;
	HandleInput *handleInput = NULL;
	Player player;
	Clock timer;
	vector<IDrawAble*> gameObjects;
	GUIMaster *gui = NULL;
	View *view = NULL;

	Areas newArea = Areas::Base;
	Areas lastArea = Areas::Base;	
	BaseGameArea *baseGameArea = NULL;
	SurvivalGameArea *survivalGameArea = NULL;
	HostileGameArea *hostileGameArea = NULL;
	FinalGameArea *finalGameArea = NULL;
	IGameArea *currentGameArea = NULL;

	void EnterNewArea(RenderWindow *window, View *view);
	GameObject *triggerdObject = NULL;
	void ExecuteObjectTrigger(RenderWindow *window);

	

	int amountOfDaysLeft = 50;
};

