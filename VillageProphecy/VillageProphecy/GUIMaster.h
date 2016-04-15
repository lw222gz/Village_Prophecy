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
				GameObject *triggerdObj);

	void setQuickMenu(GameObject *obj);
	void quickMenuNotTriggerd();
	void triggerQuickMenu();
	bool isQuickMenuActive();

private:
	Sprite inGameMenuSprite;
	Texture inGameMenuTexture;

	Font coolvetica;
	Text displayText;

	Sprite quickMenuSprite;
	Texture quickMenuTexture;
	
	template <class T>
	string getStringRepresentation(T);
};

