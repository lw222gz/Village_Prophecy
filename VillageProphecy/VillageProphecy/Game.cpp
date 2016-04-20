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
	RenderWindow window = RenderWindow(VideoMode(windowWidth, windowHeight), "Village Prophecy");
	view = View(Vector2f(720, 450), Vector2f(1440, 900));
	window.setView(view);
	
	while (window.isOpen()){
		//Clear window
		window.clear(Color::White);
		switch (currentGameState)
		{
		case GameState::Play:
			gameLoop.RunGame(&window);
			
			if (gameLoop.GameOver()){
				currentGameState = GameState::GameOver;
			}
			//play game
			break;

		case GameState::GameOver:
			window.clear(Color::White);
			gui.DrawGameOver(&window, &view);		
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
