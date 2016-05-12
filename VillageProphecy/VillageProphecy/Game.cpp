#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

/*
* <DESCRIPTION>
* Main game loop, controls the game with a GameState status. Loops until the game is closed.
*/
void Game::StartGame(){
	RenderWindow window = RenderWindow(VideoMode(windowWidth, windowHeight), "Village Prophecy", Style::Titlebar);
	view = View(Vector2f(720, 450), Vector2f(1440, 900));
	
	window.setView(view);
	
	while (window.isOpen()){	
		//Clear window		
		switch (currentGameState)
		{
			case GameState::Play:
				//TODO: draw background.
				window.clear(Color::White);
				gui.DrawGameGrassBackground(&window, gameLoop.getCurrentGameArea());

				gameLoop.RunGame(&window);
			
				if (gameLoop.GameOver()){
					currentGameState = GameState::GameOver;
				}
				else if (gameLoop.GameWon()){
					currentGameState = GameState::GameWon;
				}
				else if (gameLoop.switchToCombat()){
					currentGameState = GameState::Combat;
					gameCombatLoop.InitiateCombatLoopValues();
				}
				//play game
				break;

			case GameState::GameOver:
				window.clear(Color::White);
				gui.DrawGameOver(&window, &view);		
				break;

			case GameState::Combat:
				//The game freezes the screen and when the transission animation has covered the 
				//screen normal rendering is resumed.
				if (gameCombatLoop.isNormalRenderingActive()){
					window.clear(Color::White);
					gui.DrawGameCombatGrassBackground(&window, &view);
				}

				gameCombatLoop.runCombatLoop(&window, gameLoop.getCombatEnemies());
				
				if (gameCombatLoop.IsCombatOver()){
					currentGameState = GameState::Play;
					gameLoop.getPlayerPointer()->setToSavedPosition();
					gameLoop.CombatOver();
					//IMPORTANT - When switching back to GameState::Play the timer in GameLoop.cpp must be reset
				}
				else if (gameCombatLoop.IsGameOver()){
					currentGameState = GameState::GameOver;
				}
				
				break;

			case GameWon:
				window.clear(Color::White);
				gui.DrawGameWon(&window, &view);
				break;

			default:
				throw "Not in a gamestate";
				break;
		}

		Event event;
		while (window.pollEvent(event))
		{
			
			// "close requested" event: we close the window
			if (event.type == Event::Closed){
				window.close();
			}
		}

		//TODO: Switch to change menu
		//Temp key for faster testing
		//If player presses ESC then the window should close
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}

		//End the current frame
		window.display();
	}
	
}
