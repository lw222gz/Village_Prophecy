#pragma once
#include "GameLoop.h"
#include "GameState.h"
#include "GameCombatLoop.h"
#include "InGameMenuGUI.h"

#pragma once
class Game
{
public:
	Game();
	~Game();
	void StartGame();

private:	
	View view;
	GameState currentGameState = GameState::Play;
	GUIMaster gui;
	HandleInput handleInput;
	InGameMenuGUI inGameMenuGUI = InGameMenuGUI(&view);
	GameLoop gameLoop = GameLoop(&view, &gui, &inGameMenuGUI, &handleInput);
	GameCombatLoop gameCombatLoop = GameCombatLoop(&view, gameLoop.getPlayerPointer(), &inGameMenuGUI, &handleInput);
	
	float windowHeight = 900;
	float windowWidth = 1440;
};

