#pragma once
#include "Player.h"
#include "Enemy.h"
#include "CombatState.h"
#include "GameMessage.h"

class CombatGUI
{
public:
	CombatGUI(View *gameView);
	~CombatGUI();
	void DrawCombatPhase(RenderWindow *window, Time *t, Player *p, vector<Enemy*> *enemies);
	void TransitionAnimation(RenderWindow *window, Time *t);
	void DrawTargetArrow(RenderWindow *window, int targetIndex);

	void DrawCombatText(RenderWindow *window, Time *t);
	void AddCombatText(string mess, int target);

	bool isNormalRenderingActive();
	bool isTransitionAnimationOver();
	void ResetAnimationValues();
	

private:
	View *view;
	const float transitionAnimationTime = 1;
	//Positions of enemies, they player can meet up to 3 at once.
	vector<Vector2f> enemyPositions;
	float currentAnimationTime = 0;
	float percentComplete = 0;
	RectangleShape rect;

	RectangleShape enemyHpBar;
	RectangleShape enemyHpBehindBar;

	Transform transformation;
	void ResetTransformation(RenderWindow *window);

	string getEnemyName(EnemyType type);

	Font coolvetica;
	Text displayText;

	Texture targetArrowTexture;
	Sprite targetArrowSprite;

	vector<GameMessage*> combatMessages;
};

