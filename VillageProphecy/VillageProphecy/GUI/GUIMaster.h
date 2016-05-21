#pragma once
#include "../BaseClasses/IGameArea.h"
#include "GameMessage.h"
#include "TextureLoader.h"


using namespace sf;
using namespace std;

class GUIMaster
{
public:
	GUIMaster(TextureLoader *textures);
	~GUIMaster();
	void DrawGame(vector<IDrawAble*> gameObjects, 
				vector<VisualEnemy*> *areaEnemies,
				RenderWindow *window, 
				View *gameView, 
				Player *player,
				IGameObject *triggerdObj,
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
	TextureLoader *textures;
	bool sleepAnimationActive = false;
	float currentAnimationTime = 0;
	const float sleepFadeTime = 2;
	const float sleepTime = 5;
	const float sleepFadeBackTime = 7;	
	string sleepMessage = "";
	RectangleShape screenCoverRect;

	RectangleShape confirmationBox;

	Text displayText;

	Sprite quickMenuSprite;
	Sprite gameOverSprite;
	Sprite gameWonSprite;
	Sprite GrassBackgroundSprite;

	vector<GameMessage*> gameAlerts;
	
	template <class T>
	string getStringRepresentation(T);

};

