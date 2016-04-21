#pragma once
#include "Player.h"

class CombatGUI
{
public:
	CombatGUI(View *gameView);
	~CombatGUI();
	void DrawCombatPhase(RenderWindow *window, Time *t, Player *p);
	void TransitionAnimation(RenderWindow *window, Time *t);

	bool isNormalRenderingActive();
	bool isTransitionAnimationOver();
	void ResetAnimationValues();

private:
	View *view;
	const float transitionAnimationTime = 3.0;
	float currentAnimationTime = 0;
	float percentComplete = 0;
	RectangleShape rect;

};

