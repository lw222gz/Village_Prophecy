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


	enemyHpBar.setFillColor(Color::Red);
	enemyHpBehindBar.setFillColor(Color::Black);

}


CombatGUI::~CombatGUI()
{
}

void CombatGUI::DrawCombatPhase(RenderWindow *window, Time *t, Player *p, vector<Enemy*> *enemies){

	ResetTransformation(window);
	window->draw(p->getSprite(), transformation);

	for (int i = 0; i < enemies->size(); ++i){

		if (enemies->at(i)->IsAlive()){
			ResetTransformation(window);
			transformation.translate(enemyPositions[i]);
			window->draw(enemies->at(i)->getSprite(), transformation);

			displayText.setString(getEnemyName(enemies->at(i)->getEnemyType()));

			transformation.translate(0, -20);
			enemyHpBehindBar.setSize(Vector2f(enemies->at(i)->getSprite().getTexture()->getSize().x, 10));

			enemyHpBar.setSize(Vector2f(
				enemies->at(i)->getSprite().getTexture()->getSize().x * (enemies->at(i)->getHitPoints() / enemies->at(i)->getMaxHitPoints())
				, 10));

			window->draw(enemyHpBehindBar, transformation);
			window->draw(enemyHpBar, transformation);

			enemies->at(i)->getSprite().getTexture()->getSize();

			transformation.translate(0, -25);
			window->draw(displayText, transformation);
		}
		else {
			//TODO: draw dead enemy
		}
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

void CombatGUI::DrawEnemyAttackAnimation(Enemy *enemy, float currentTurnTime, float maxTurnTime){
	float percentComplete = currentTurnTime / maxTurnTime;
	if (percentComplete <= .05){
		enemy->setPosition(-(percentComplete * 75 * 20), 0);
	}
	//TODO: add animation for the enemy walking back.
	else if(percentComplete >= .5){
		enemy->setPosition(0, 0);
	}
}

void CombatGUI::DrawTargetArrow(RenderWindow *window, int targetIndex){
	ResetTransformation(window);
	transformation.translate(enemyPositions[targetIndex]);
	transformation.translate(10, -100);

	window->draw(targetArrowSprite, transformation);
}

//TODO: the player will need his own addcombattext method because it will
//require the player parameter anyway
void CombatGUI::AddCombatText(string mess, int targetIndex){
	combatMessages.push_back(new GameMessage(mess, enemyPositions[targetIndex], true, .5));
}


void CombatGUI::AddPlayerCombatText(string mess, Player *player){
	combatMessages.push_back(new GameMessage(mess, player->getPosition(), true, .5));
	
}

void CombatGUI::AddStatusCombatText(EnemyType enemyType){
	combatMessages.push_back(new GameMessage("An Enemy " + getEnemyStringRepresentation(enemyType) + " Attacked You!", statusMessagePosition, true, 1.5));
}

void CombatGUI::AddStatusText(string mess){
	combatMessages.push_back(new GameMessage(mess, statusMessagePosition, true, 1.5));
}


//Draw combat messages
void CombatGUI::DrawCombatText(RenderWindow *window, Time *t){
	for (int i = 0; i < combatMessages.size(); ++i){
		ResetTransformation(window);
		transformation.translate(0, -50);

		combatMessages[i]->updateMessageTimer(t->asSeconds());
		//if the message life time is over then it will be removed and the next
		//loop iteration will begin.
		if (combatMessages[i]->getLifeTimePercent() >= 1){
			delete combatMessages[i];  
			combatMessages.erase(combatMessages.begin() + i);
			continue;
		}
		//transformation.translate(enemyPositions[0]);//combatMessages[i]->getMessage().getPosition());
		//transformation.translate(-100, 20);//combatMessages[i]->getLifeTimePercent() * 50
		if (combatMessages[i]->IsMoving()){
			combatMessages[i]->addToCurrentPosition(Vector2f(0, combatMessages[i]->getTextSpeed() * t->asSeconds()));
		}
		
		window->draw(combatMessages[i]->getMessage(), transformation);
	}
}

bool CombatGUI::isNormalRenderingActive(){
	return percentComplete >= 1;
}

bool CombatGUI::isTransitionAnimationOver(){
	return percentComplete >= 2;
}

void CombatGUI::ResetTransitionAnimationValues(){
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


string CombatGUI::getEnemyStringRepresentation(EnemyType enemyType){
	switch (enemyType)
	{
	case Skeleton_MELEE:
		return "Skeleton Warrior";

	case Human_MELEE:
		return "Human Warrior";

	default:
		return "Unknown";
	}
}