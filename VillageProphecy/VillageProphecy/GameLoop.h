#pragma once
#include "Player\Player.h"
#include "HandleInput.h"
#include "GUI\GUIMaster.h"
#include "GUI\InGameMenuGUI.h"
#include "Enums\GameAreas.h"
#include "GameFields\GameAreas\SurvivalGameArea.h"
#include "GameFields\GameAreas\HostileGameArea.h"
#include "GameFields\GameAreas\FinalGameArea.h"
#include "GameFields\GameAreas\BaseGameArea.h"
#include "BaseClasses/IGameArea.h"

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
	GameLoop(View *view, 
		GUIMaster *gui, 
		InGameMenuGUI *inGameMenuGUI, 
		HandleInput *inputHandler,
		TextureLoader *textures);
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
	TextureLoader *textures;
	InGameMenuGUI *gameMenuGUI;
	bool playerEnteredCombatPhase = false;
	int enemyVectorIndex = 0;
	bool isGameOver = false;
	Time timeElapsed;
	HandleInput *handleInput = NULL;
	Player *player = NULL;
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
	IGameObject *triggerdObject = NULL;
	void ExecuteObjectTrigger(RenderWindow *window);

	int amountOfDaysLeft = 50;
};

