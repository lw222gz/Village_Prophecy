#include "GameLoop.h"

GameLoop::GameLoop() {
	survivalGameArea = new GameArea(Areas::Survival, Vector2u(3000, 1500));
	hostileGameArea = new GameArea(Areas::Hostile, Vector2u(4000, 1000));
	baseGameArea = new GameArea(Areas::Base, Vector2u(1440, 900));

	//A game will allways start in the baseGameArea
	currentGameArea = baseGameArea;
	lastArea = Areas::Base;
	player.setAreaPaths(currentGameArea->getAreaPaths());
	player.setBorders(currentGameArea->getAreaSize());
}


GameLoop::~GameLoop()
{
}


void GameLoop::StartLoop(){

	RenderWindow window = RenderWindow(VideoMode(1440, 900), "Village Prophecy");
	view = View(Vector2f(720,450), Vector2f(1440, 900));
	window.setView(view);

	Clock timer;

	while (window.isOpen())
	{
		//gets timer time
		timeElapsed = timer.getElapsedTime();
		//resets timer instantly after to reuse getElapsedTime to get the time for the loop iteration
		timer.restart();
		
		//Checks for user input
		newArea = inputHandler.CheckUserInput(&player, &timeElapsed);
		if (newArea != Areas::None){
			EnterNewArea(&window);
		}
		

		Event event;
		while (window.pollEvent(event))
		{		
			// "close requested" event: we close the window
			if (event.type == Event::Closed){
				window.close();
			}
		}
		//If player presses ESC then the window should close
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}

		for (int i = 0; i < currentGameArea->getAreaObjects().size(); ++i){
			if(currentGameArea->getAreaObjects()[i]->isTriggerd(&player)){
				currentGameArea->getAreaObjects()[i]->TriggerdEffect();
			}
		}
		
		
		//TEST CODE!
		if (lastArea == Areas::Survival){
			Texture test;
			if (!test.loadFromFile("Textures/PHTest.png")){
				throw "Test img did not load correctly.";
			}
			Sprite s;
			s.setTexture(test);
			s.setPosition(Vector2f(1200, 100));

			window.draw(s);

			s.setPosition(Vector2f(2800, 100));
			window.draw(s);
		}
		//END TEST CODE

		//Clear window
		window.clear(Color::White);

		//Camera movement, changes the values of the view to follow the player
		//moves camera X-led
		if (player.getPosition().x >= window.getSize().x / 2 && 
			player.getPosition().x + window.getSize().x/2 < currentGameArea->getAreaSize().x){

			view.setCenter((window.getSize().x / 2) + (player.getPosition().x - window.getSize().x / 2), view.getCenter().y);
			window.setView(view);
		}
		//moves camera Y-led
		if (player.getPosition().y >= window.getSize().y / 2 &&
			player.getPosition().y + window.getSize().y / 2 < currentGameArea->getAreaSize().y){

			view.setCenter(view.getCenter().x, (window.getSize().y / 2) + (player.getPosition().y - window.getSize().y / 2));
			window.setView(view);
		}
		//draw the game
		gui.DrawGame(currentGameArea->getAreaVisualObjects(), &window, &view, &player);
		
		// end the current frame
		window.display();
		
	}
}

void GameLoop::EnterNewArea(RenderWindow *window){
	switch (newArea)
	{
	case Base:
		currentGameArea = baseGameArea;
		break;
	case Survival:
		currentGameArea = survivalGameArea;
		break;
	case Hostile:
		currentGameArea = hostileGameArea;
		break;
	case Dungeon:

		break;
	case Final:
		break;
	case None:
		break;
	default:
		break;
	}

	int y;
	int x = currentGameArea->getAreaSize().x - window->getSize().x / 2;
	if (x < window->getSize().x / 2){
		x = window->getSize().x / 2;
	}
	for (unsigned int i = 0; i < currentGameArea->getAreaPaths().size(); ++i){
		//gets the path that leads back to the last area to set the player position.
		if (currentGameArea->getAreaPaths()[i]->getNextArea() == lastArea){
			player.setPlayerPosition(currentGameArea->getAreaPaths()[i]->getPosition());
			lastArea = newArea;

			y = currentGameArea->getAreaPaths()[i]->getPosition().y + currentGameArea->getAreaPaths()[i]->getSize().y / 2;

			if (currentGameArea->getAreaPaths()[i]->getPosition().x == 0){
				x = window->getSize().x / 2;
			}
			break;
		}
	}
	player.setAreaPaths(currentGameArea->getAreaPaths());
	player.setBorders(currentGameArea->getAreaSize());
	
	
	view.setCenter(x, y);
	window->setView(view);
}