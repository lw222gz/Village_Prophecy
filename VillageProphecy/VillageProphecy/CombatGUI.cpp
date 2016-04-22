#include "CombatGUI.h"


CombatGUI::CombatGUI(View *gameView) 
	: view(gameView)
{	
	enemyPositions = { Vector2f(1000, 300), Vector2f(1100, 100), Vector2f(1100, 500) };

	if (!coolvetica.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}

	if (!targetArrowTexture.loadFromFile("Textures/PHTargetArrow.png")){
		throw "TEXTURE LOAD ERROR: Could not load target arrow texture.";
	}
	targetArrowSprite.setTexture(targetArrowTexture);

	//Text settings
	displayText.setFont(coolvetica);
	displayText.setCharacterSize(16);
	displayText.setColor(Color::Black);
	//displayText.setStyle(Text::Bold);
}


CombatGUI::~CombatGUI()
{
}

void CombatGUI::DrawCombatPhase(RenderWindow *window, Time *t, Player *p, vector<Enemy*> *enemies){
	//TODO: draw combat ui	
	window->draw(p->getSprite());
	for (int i = 0; i < enemies->size(); ++i){

		ResetTransformation(window);
		transformation.translate(enemyPositions[i]);
		window->draw(enemies->at(i)->getSprite(), transformation);
		
		displayText.setString(getEnemyName(enemies->at(i)->getEnemyType()));
		transformation.translate(0, -25);

		window->draw(displayText, transformation);

		
	}
}

string CombatGUI::getEnemyName(EnemyType type){
	switch (type)
	{
	case EnemyType::Skeleton_MELEE:
		return "Skeleton";

	case EnemyType::Human_MELEE:
		return "Human Warrior";

	default:
		return "No string rep.";
	}
}

void CombatGUI::DrawTargetArrow(RenderWindow *window, int targetIndex){
	ResetTransformation(window);
	transformation.translate(enemyPositions[targetIndex]);
	transformation.translate(10, -100);

	window->draw(targetArrowSprite, transformation);
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


//resets it's values and sets it's position to the top left corner of the screen
void CombatGUI::ResetTransformation(RenderWindow *window){
	transformation.translate(-transformation.transformPoint(0, 0));
	transformation.translate(view->getCenter().x - window->getSize().x / 2, view->getCenter().y - window->getSize().y / 2);
}