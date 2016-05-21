#pragma once
#include "GameLoop.h"
#include "Enums/GameState.h"
#include "GameCombatLoop.h"
#include "GUI/InGameMenuGUI.h"


#pragma once
class Game
{
public:
	Game();
	~Game();
	void StartGame();

private:	
	TextureLoader gameTextures;
	View view;
	GameState currentGameState = GameState::Play;
	GUIMaster gui = GUIMaster(&gameTextures);
	HandleInput handleInput;
	InGameMenuGUI inGameMenuGUI = InGameMenuGUI(&view, &gameTextures);
	GameLoop gameLoop = GameLoop(&view, &gui, &inGameMenuGUI, &handleInput, &gameTextures);
	GameCombatLoop gameCombatLoop = GameCombatLoop(&view, gameLoop.getPlayerPointer(), &inGameMenuGUI, &handleInput, &gameTextures);
	
	float windowHeight = 900;
	float windowWidth = 1440;
};

