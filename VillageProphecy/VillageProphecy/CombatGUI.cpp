#include "CombatGUI.h"

/*
* <DESCRIPTION>
* CombatGUI constructor
* Sets enemy position values and loads in fonts and sets defualt font settings.
*
* @PARAMS
* gameView: pointer to a View object that should represent the game view.
*/
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


/*
* <DESCRIPTION>
* Draws the main combat phase positions of the enemies and player.
* The positions of the enemies are pre-set and depending on their position in the vector
* determines the position they get in the enemyPosotions vector.
*
* @PARAMS
* window: pointer to the game window object.
* t: pointer to Time object contaning the time for the current iteration of the loop
* p: pointer to the Player object of the game
* enemies: pointer to vector contaning Enemy object pointers, these are all of the enemies the player
* is facing this combat phase.
*/
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


/*
* @RETURNS
* returns a string representation of an EnemyType enum value.
*/
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


/*
* <DESCRIPTION>
* Draws the animation for an enemy attacking by moving their positing forward in a fast manner and then
* reseting the position.
*
* @PARAMS
* enemy: pointer to Enemy object that is attacking.
* currentTurnTime: float representing the time currently spent in this enemy turn as seconds.
* maxTurnTime: float representing the time that will be spent in this enemy turn as seconds.
*/
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


/*
* <DESCRIPTION>
* Draws the arrow indicating the target choosing of the player.
*
* @PARAMS
* window: pointer to the game window object.
* targetIndex: integer value representing the index of the enemy in the enemies vector.
*/
void CombatGUI::DrawTargetArrow(RenderWindow *window, int targetIndex){
	ResetTransformation(window);
	transformation.translate(enemyPositions[targetIndex]);
	transformation.translate(10, -100);

	window->draw(targetArrowSprite, transformation);
}

/*
* <DESCRIPTION>
* Adds a damage display text for an enemy.
*
* @PARAMS
* mess: string representing the text value that is being displayed.
* targetIndex: index of the enemy that is taking damage.
*/
void CombatGUI::AddCombatText(string mess, int targetIndex){
	combatMessages.push_back(new GameMessage(mess, enemyPositions[targetIndex], true, .5));
}

/*
* <DESCRIPTION>
* Adds a damage display text for the player.
*
* @PARAMS
* mess: string representation of the message.
* player: pointer to the game Player object.
*/
void CombatGUI::AddPlayerCombatText(string mess, Player *player){
	combatMessages.push_back(new GameMessage(mess, player->getPosition(), true, .5));
	
}

/*
* <DESCRIPTION>
* Adds a status text of when an enemy attacks the player.
*
* @PARAMS
* enemyType: EnemyType enum representing the type of enemy that attacked the player.
*/
void CombatGUI::AddStatusCombatText(EnemyType enemyType){
	combatMessages.push_back(new GameMessage("An Enemy " + getEnemyName(enemyType) + " Attacked You!", statusMessagePosition, true, 1.5));
}

/*
* <DESCRIPTION>
* Adds a status text message
*
* @PARAMS
* mess: string representing the message to be displayed.
*/
void CombatGUI::AddStatusText(string mess){
	combatMessages.push_back(new GameMessage(mess, statusMessagePosition, true, 1.5));
}


/*
* <DESCRIPTION>
* Draws all current combat text messages.
*
* @PARAMS
* window: pointer to the game window object.
* t: pointer to Time object contaning the amount of time spent in the current iteration of the game loop
*/
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


/*
* @RETURNS
* returns boolean, true if the transission animation is 50% complete, otherwise false.
*/
bool CombatGUI::isNormalRenderingActive(){
	return percentComplete >= 1;
}

/*
* @RETURNS
* returns boolean, true if the transission animation is over, otherwise false.
*/
bool CombatGUI::isTransitionAnimationOver(){
	return percentComplete >= 2;
}

/*
* <DESCRIPTION>
* Resets the values for the transission animation.
*/
void CombatGUI::ResetTransitionAnimationValues(){
	percentComplete = 0;
	currentAnimationTime = 0;
}


/*
* <DESCRIPTION>
* Draws the transition animation.
*
* @PARAMS
* window: pointer to the game window object.
* t: pointer to Time object contaning the time spent in the current iteration of the loop.
*/
void CombatGUI::TransitionAnimation(RenderWindow *window, Time *t){
	currentAnimationTime += t->asSeconds();
	percentComplete = currentAnimationTime / (transitionAnimationTime/2);
	

	rect.setSize(Vector2f(window->getSize().x, window->getSize().y));
	rect.setFillColor(Color::Black);
	rect.setPosition(view->getCenter().x - window->getSize().x/2, 
		(view->getCenter().y - (window->getSize().y / 2) - rect.getSize().y) + (rect.getSize().y * percentComplete));

	window->draw(rect);
}


/*
* <DESCRIPTION>
* Resets the transformation object object values and sets it's position to the top left of the screen.
*
* @PARAMS
* window: pointer to the game window object.
*/
void CombatGUI::ResetTransformation(RenderWindow *window){
	transformation.translate(-transformation.transformPoint(0, 0));
	transformation.translate(view->getCenter().x - window->getSize().x / 2, view->getCenter().y - window->getSize().y / 2);
}

/*
* <DESCRIPTION>
* Empties the combatMessages vector
*/
void CombatGUI::ResetMessages(){
	combatMessages.clear();
}