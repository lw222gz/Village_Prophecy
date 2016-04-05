#pragma once
#include "IDrawAble.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GUIMaster
{
public:
	GUIMaster();
	~GUIMaster();
	void DrawGame(vector<IDrawAble*> gameObjects, RenderWindow *window);
};

