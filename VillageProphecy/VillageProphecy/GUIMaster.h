#pragma once
#include "GameObject.h"
#include "IGameArea.h"
#include "GameMessage.h"


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
	void DrawGameGrassBackground(RenderWindow *window, IGameArea *area);
	void DrawGameOver(RenderWindow *window, View *view);
	void DrawGameWon(RenderWindow *window, View *view);
	void DrawConfirmationBox(RenderWindow *window, View *view, string question);

	void AddGameAlert(string mess, Vector2f position);
	void setQuickMenu(GameObject *obj);
	void quickMenuNotTriggerd();
	void triggerQuickMenu();
	bool isQuickMenuActive();

	void activateSleepAnimation(Vector2f screenSize, bool hasFire);
	void sleepAnimation(RenderWindow *window, Time *t);
	float getSleepAnimationTime();

private:
	bool sleepAnimationActive = false;
	float currentAnimationTime = 0;
	const float sleepFadeTime = 2;
	const float sleepTime = 5;
	const float sleepFadeBackTime = 7;	
	string sleepMessage = "";
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

	vector<GameMessage*> gameAlerts;
	
	template <class T>
	string getStringRepresentation(T);
};

