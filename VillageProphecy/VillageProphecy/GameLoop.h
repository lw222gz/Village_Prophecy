#pragma once
#include "Player.h"
#include "IDrawAble.h"
#include "HandleInput.h"
#include "GUIMaster.h"
#include "GameArea.h"
#include "GameAreas.h"
#include "GameObject.h"
#include "TriggerType.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class GameLoop
{
public:
	GameLoop();
	~GameLoop();
	void StartLoop();

private:
	Time timeElapsed;
	HandleInput inputHandler;
	Player player;
	vector<IDrawAble*> gameObjects;
	GUIMaster gui;
	Areas newArea = Areas::No_Area;
	Areas lastArea = Areas::No_Area;
	GameArea *currentGameArea = NULL;
	GameArea *baseGameArea = NULL;
	GameArea *survivalGameArea = NULL;
	GameArea *hostileGameArea = NULL;
	View view;
	void EnterNewArea(RenderWindow *window);
	GameObject *triggerdObject = NULL;
	void ExecuteObjectTrigger();
};

