#include "GameLoop.h"

GameLoop::GameLoop() {
	survivalGameArea = new GameArea(Areas::Survival, Vector2u(3000, 970), &player);
	hostileGameArea = new GameArea(Areas::Hostile, Vector2u(4000, 1000), &player);
	baseGameArea = new GameArea(Areas::Base, Vector2u(1440, 900), &player);

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

	RenderWindow window(VideoMode(1440, 900), "Village Prophecy");
	View view(FloatRect(Vector2f(0,0), Vector2f(1440, 900)));
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
			EnterNewArea();
		}
		

		Event event;
		while (window.pollEvent(event))
		{		
			// "close requested" event: we close the window
			if (event.type == Event::Closed){
				window.close();
			}

			
			
		}

		//Clear window
		window.clear(Color::White);
		
		gui.DrawGame(currentGameArea->getAreaObjects(), &window);

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
		}

		if (player.getPosition().x >= window.getSize().x / 2){

			view.move(player.getPosition().x - window.getSize().x / 2,
						player.getPosition().y - window.getSize().y / 2);
		}
		

		// end the current frame
		window.display();
		
	}
}

void GameLoop::EnterNewArea(){
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

	for (int i = 0; i < currentGameArea->getAreaPaths().size(); ++i){
		//gets the path that leads back to the last area to set the player position.
		if (currentGameArea->getAreaPaths()[i]->getNextArea() == lastArea){
			player.setPlayerPosition(currentGameArea->getAreaPaths()[i]->getPosition());
			lastArea = newArea;
			break;
		}
	}
	player.setAreaPaths(currentGameArea->getAreaPaths());
	player.setBorders(currentGameArea->getAreaSize());
}