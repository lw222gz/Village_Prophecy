#pragma once
#include "Player.h"
#include "CombatOptions.h"

class InGameMenuGUI
{
public:
	InGameMenuGUI(View *gameView);
	~InGameMenuGUI();
	void DrawGameMenu(RenderWindow *window, Player *player);
	void DrawCombatMenu(RenderWindow *window, Player *player, CombatOptions *currentOption);

private:
	View *view;
	Transform transformation;

	Texture optionPointerTexture;
	Sprite optionPointerSprite;

	RectangleShape XPBar;
	RectangleShape behindXPBar;

	RectangleShape behindHPBar;
	RectangleShape hpBar;

	RectangleShape behindStatBar;
	RectangleShape statBar;

	Sprite inGameMenuSprite;
	Texture inGameMenuTexture;

	Font coolvetica;
	Text displayText;

	string getStringRepPlayerLevel(LevelEXPRequirement currlevel);
	string getStringRepCombatOptions(CombatOptions option);
	void ResetTransformation(Vector2u windowSize);

	void DrawBaseMenu(RenderWindow *window);
	void DrawXPBar(RenderWindow *window, Player *player);
	void DrawPlayerStats(RenderWindow *window, Player *player);
	void DrawCombatOptions(RenderWindow *window, CombatOptions *currentOption);
	void DrawPlayerInventory(RenderWindow *window, Player *player);
	void DrawPlayerActionPoints(RenderWindow *window, Player *player);
};

