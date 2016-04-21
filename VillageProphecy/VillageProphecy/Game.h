#include "GameLoop.h"
#include "GameState.h"
#include "GameCombatLoop.h"

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
	GameLoop gameLoop = GameLoop(&view, &gui);
	GameCombatLoop gameCombatLoop = GameCombatLoop(&view, gameLoop.getPlayerPointer());
	
	float windowHeight = 900;
	float windowWidth = 1440;
};

