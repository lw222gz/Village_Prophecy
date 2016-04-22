#pragma once
#include "Player.h"
#include "Enemy.h"
#include "CombatState.h"

class CombatGUI
{
public:
	CombatGUI(View *gameView);
	~CombatGUI();
	void DrawCombatPhase(RenderWindow *window, Time *t, Player *p, vector<Enemy*> *enemies);
	void TransitionAnimation(RenderWindow *window, Time *t);
	void DrawTargetArrow(RenderWindow *window, int targetIndex);

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

	Transform transformation;
	void ResetTransformation(RenderWindow *window);

	string getEnemyName(EnemyType type);

	Font coolvetica;
	Text displayText;

	Texture targetArrowTexture;
	Sprite targetArrowSprite;
};

