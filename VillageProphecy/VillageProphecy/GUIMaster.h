#pragma once
//#include "IDrawAble.h"
//#include "Player.h"
#include "GameObject.h"
#include "GameArea.h"
//#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GUIMaster
{
public:
	GUIMaster();
	~GUIMaster();
	void DrawGame(vector<IDrawAble*> gameObjects, 
				RenderWindow *window, 
				View *gameView, 
				Player *player,
				GameObject *triggerdObj,
				Time *t,
				int amountOfDaysLeft);

	void DrawGameCombatGrassBackground(RenderWindow *window, View *view);
	void DrawGameGrassBackground(RenderWindow *window, GameArea *area);
	void DrawGameOver(RenderWindow *window, View *view);
	void DrawGameWon(RenderWindow *window, View *view);
	void DrawConfirmationBox(RenderWindow *window, View *view, string question);

	void setQuickMenu(GameObject *obj);
	void quickMenuNotTriggerd();
	void triggerQuickMenu();
	bool isQuickMenuActive();

	void activateSleepAnimation(Vector2f screenSize);
	void sleepAnimation(RenderWindow *window, Time *t);
	float getSleepAnimationTime();

private:
	bool sleepAnimationActive = false;
	float currentAnimationTime = 0;
	const float sleepTime = .5;
	float sleepAnimationTime = 4;
	RectangleShape screenCoverRect;

	RectangleShape confirmationBox;

	Font coolvetica;
	Text displayText;

	Sprite quickMenuSprite;
	Texture quickMenuTexture;

	Sprite gameOverSprite;
	Texture gameOverTexture;

	Sprite gameWonSprite;
	Texture gameWonTexture;

	Sprite GrassBackgroundSprite;
	Texture GrassBackgroundTexture;
	
	template <class T>
	string getStringRepresentation(T);
};

