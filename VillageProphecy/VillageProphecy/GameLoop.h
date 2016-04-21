#pragma once
#include "Player.h"
//Inventory
#include "HandleInput.h"
#include "GUIMaster.h"
#include "GameArea.h"
//#include "GameObject.h"
//#include "TriggerType.h"
//#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class GameLoop
{
public:
	GameLoop(View *view, GUIMaster *gui);
	~GameLoop();
	void RunGame(RenderWindow *window);
	bool GameOver();
	bool switchToCombat();
	Player* getPlayerPointer();
	vector<Enemy*>* getCombatEnemies();

private:
	bool playerEnteredCombatPhase = false;
	int enemyVectorIndex = 0;
	bool isGameOver = false;
	Time timeElapsed;
	HandleInput handleInput;
	Player player;
	Clock timer;
	vector<IDrawAble*> gameObjects;
	GUIMaster *gui = NULL;
	View *view = NULL;
	Areas newArea = Areas::No_Area;
	Areas lastArea = Areas::No_Area;
	GameArea *currentGameArea = NULL;
	GameArea *baseGameArea = NULL;
	GameArea *survivalGameArea = NULL;
	GameArea *hostileGameArea = NULL;
	void EnterNewArea(RenderWindow *window, View *view);
	GameObject *triggerdObject = NULL;
	void ExecuteObjectTrigger(RenderWindow *window);
	int amountOfDaysLeft = 50;
};

