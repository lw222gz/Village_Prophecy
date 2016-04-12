#pragma once
#include "Player.h"
#include "MoveDirection.h"
#include "GameAreas.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class HandleInput
{
public:
	HandleInput();
	~HandleInput();
	Areas CheckUserInput(Player *player, Time *t);

	bool checkQuickMenuInput();

private:
	Areas area = Areas::No_Area;
};

