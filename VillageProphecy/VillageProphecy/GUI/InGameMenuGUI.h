#pragma once
#include "../Player/Player.h"
#include "../Enums/CombatOptions.h"
#include "TextureLoader.h"
//#include <math.h>


class InGameMenuGUI
{
public:
	InGameMenuGUI(View *gameView, TextureLoader *textures);
	~InGameMenuGUI();
	void DrawGameMenu(RenderWindow *window, Player *player);
	void DrawCombatMenu(RenderWindow *window, Player *player);
	void DrawSkillOptions(RenderWindow *window, Player *player, int currentSkillIndex);
	void DrawCombatOptions(RenderWindow *window, CombatOptions currentOption);
	

private:
	View *view;
	Transform transformation;

	Sprite optionPointerSprite;

	RectangleShape XPBar;
	RectangleShape behindXPBar;

	RectangleShape behindHPBar;
	RectangleShape hpBar;

	RectangleShape behindStatBar;
	RectangleShape statBar;

	RectangleShape skillOptionBackground;
	RectangleShape skillDescriptionBox;

	Sprite inGameMenuSprite;

	Text displayText;

	string getStringRepPlayerLevel(LevelEXPRequirement currlevel);
	string getStringRepCombatOptions(CombatOptions option);
	void ResetTransformation(Vector2u windowSize);
	string AddRowsToString(string str, int breakPoint, int currentIndex);
	string getStringRepConsumeType(SkillConsumeableStats consumeableStat);

	void DrawBaseMenu(RenderWindow *window);
	void DrawXPBar(RenderWindow *window, Player *player);
	void DrawPlayerStats(RenderWindow *window, Player *player);
	
	void DrawPlayerInventory(RenderWindow *window, Player *player);
	void DrawPlayerActionPoints(RenderWindow *window, Player *player);
};
