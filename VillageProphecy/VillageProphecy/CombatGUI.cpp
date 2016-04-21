#include "CombatGUI.h"


CombatGUI::CombatGUI(View *gameView) 
	: view(gameView)
{	
	
}


CombatGUI::~CombatGUI()
{
}

void CombatGUI::DrawCombatPhase(RenderWindow *window, Time *t, Player *p){
	//TODO: draw combat ui	
	window->draw(p->getSprite());
}

bool CombatGUI::isNormalRenderingActive(){
	return percentComplete >= 1;
}

bool CombatGUI::isTransitionAnimationOver(){
	return percentComplete >= 2;
}

void CombatGUI::ResetAnimationValues(){
	percentComplete = 0;
	currentAnimationTime = 0;
}

//Draws transition animation
void CombatGUI::TransitionAnimation(RenderWindow *window, Time *t){
	currentAnimationTime += t->asSeconds();
	percentComplete = currentAnimationTime / (transitionAnimationTime/2);
	

	rect.setSize(Vector2f(window->getSize().x, window->getSize().y));
	rect.setFillColor(Color::Black);
	rect.setPosition(view->getCenter().x - window->getSize().x/2, 
		(view->getCenter().y - (window->getSize().y / 2) - rect.getSize().y) + (rect.getSize().y * percentComplete));

	window->draw(rect);
}