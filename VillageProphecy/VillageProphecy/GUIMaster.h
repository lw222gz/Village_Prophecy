#pragma once
//#include "IDrawAble.h"
//#include "Player.h"
#include "GameObject.h"
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

	void DrawGameOver(RenderWindow *window, View *view);

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
	RectangleShape *rectPtr = NULL;

	RectangleShape behindHPBar;
	RectangleShape hpBar;

	RectangleShape behindStatBar;
	RectangleShape statBar;

	Sprite inGameMenuSprite;
	Texture inGameMenuTexture;

	Font coolvetica;
	Text displayText;

	Sprite quickMenuSprite;
	Texture quickMenuTexture;

	Sprite gameOverSprite;
	Texture gameOverTexture;
	
	template <class T>
	string getStringRepresentation(T);
};

