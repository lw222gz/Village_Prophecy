#pragma once
#include "IDrawAble.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

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
				Player *player);

private:
	Sprite inGameMenuSprite;
	Texture inGameMenuTexture;
};

