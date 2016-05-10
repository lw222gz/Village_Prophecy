#include "GameCombatLoop.h"
#include "EnemySkill.h"

GameCombatLoop::GameCombatLoop(View *gameView, Player *p, InGameMenuGUI *inGameMenuGUI, HandleInput *inputHandler)
	: view(gameView), player(p), combatMenuGUI(inGameMenuGUI), handleInput(inputHandler)
{
	gui = new CombatGUI(view);
}


GameCombatLoop::~GameCombatLoop()
{
}

/*
* @RETURNS
* returns boolean, true if the fight is over, otherwise false.
*/
bool GameCombatLoop::IsCombatOver(){
	return (currentCombatState == CombatState::Combat_Phase_Over);
}


bool GameCombatLoop::IsGameOver(){
	return (currentCombatState == CombatState::Game_Over);
}




/*
* <DESCRIPTION>
* Since there will be several diffrent enemy encounters this metod will reset some values required
* each time a new battle is initiated.
*/
void GameCombatLoop::InitiateCombatLoopValues(){
	timer.restart();
	phaseTransmissionAnimation = true;
	gui->ResetTransitionAnimationValues();
	player->setPlayerPosition(Vector2f(320, 330));
	currentOption = CombatOptions::Attack;
	currentCombatState = CombatState::Choosing_Action;
	targetIndex = 0;
	currentEnemyTurnIndex = 0;
	currentEnemyTurnTime = 0;
	phaseSwitchPause = 0;
	//removes any old combat messages
	gui->ResetMessages();
	//boolean blocking spam of "You Died!" message.
	hasDisplayedPlayerDied = false;	
	//clears any debuffs form previous battle 
	playerDebuffs.clear();
	//sets so the player faces the enemies
	player->ResetReflectSprite();
}

/*
* <DESCRIPTION>
* Then this method returns true, the game will start to clear the screen each iteration of the game loop.
*
* @RETURNS
* returns true if normal rendering of the combat phase is active
*/
bool GameCombatLoop::isNormalRenderingActive(){
	return gui->isNormalRenderingActive();
}

/*
* <DESCRIPTION>
* Game loop for the combat phase of the game.
* Calls gui methods and controls the combat phase between the player and the enemies he/she faces.
*
* @PARAMS
* window: pointer to the game window object.
* enemies: pointer to a vector of enemies the player is facing. 
*/
//TODO: add possibilty to go back to previous options during combat
void GameCombatLoop::runCombatLoop(RenderWindow *window, vector<Enemy*> *enemies){
	
	//TODO: draw background first
	combatMenuGUI->DrawCombatMenu(window, player);

	//gets timer time
	timeElapsed = timer.getElapsedTime();
	//resets timer instantly after to reuse getElapsedTime to get the time for the loop iteration
	timer.restart();

	if (isNormalRenderingActive()){
		switch (currentCombatState)
		{
			case Choosing_Action:
				currentOption = handleInput->CheckUserCombatInput(currentOption);
				if (handleInput->CheckEnterKeyPressed()){
					ExecuteCombatOption();
				}
				combatMenuGUI->DrawCombatOptions(window, currentOption);
				break;

			case Choosing_Skill:
				combatMenuGUI->DrawSkillOptions(window, player, skillChoiceIndex);

				skillChoiceIndex = handleInput->CheckSkillChoiceInput(&timeElapsed, skillChoiceIndex, player->SkillManager()->getPlayerSkills()->size() - 1);
				
				//TODO: Add executable command for skills.
				if (handleInput->CheckEnterKeyPressed()){
					if (player->SkillManager()->getPlayerSkills()->at(skillChoiceIndex)->CanCast()){
						currentCombatState = Choosing_Skill_Target;
					}
					else {
						gui->AddStatusText("You don't have the required stats to use that skill.");
					}
					
				}
				//space key to go back to choosing action
				PlayerCanGoBack();
				break;

			case Choosing_Target:
				targetIndex = handleInput->CheckTargetChoiceInput(timeElapsed, targetIndex, enemies);
				gui->DrawTargetArrow(window, targetIndex);

				if (handleInput->CheckEnterKeyPressed()){
					PlayerDealsDamage(enemies, (int)player->StatsManager()->getPlayerAttackDamage());									
				}

				PlayerCanGoBack();
				break;

			case Choosing_Skill_Target:
				targetIndex = handleInput->CheckTargetChoiceInput(timeElapsed, targetIndex, enemies);
				gui->DrawTargetArrow(window, targetIndex);

				if (handleInput->CheckEnterKeyPressed()){
					player->SkillManager()->getPlayerSkills()->at(skillChoiceIndex)->ConsumeSkillStats();
					PlayerDealsDamage(enemies, (int)player->SkillManager()->getPlayerSkills()->at(skillChoiceIndex)->getSkillDamage());
				}

				PlayerCanGoBack();
				break;

			//Runs all enemy turns, when all enemies have executed their actions then 
			//it goes back to the players turn.
			case Enemy_Turn:
				//If all enemies have had their turns then it goes back to the player
				if (currentEnemyTurnIndex >= enemies->size()){
					currentCombatState = Player_Debuff_Tick;		
					//call NewEnemyTurn to reset turn values.
					NewEnemyTurn();
					currentEnemyTurnIndex = 0;
					break;
				}

				if (enemies->at(currentEnemyTurnIndex)->IsAlive()){
					if (attackConfirm){
						currentEnemyTurnTime += timeElapsed.asSeconds();
						gui->EnemyAttackAnimation(enemies->at(currentEnemyTurnIndex), currentEnemyTurnTime, enemyTurnTime);

						if (currentEnemyTurnTime >= enemyTurnTime){
							NewEnemyTurn();
						}
					}
					else if(!attackConfirm) {
						//If the enemy has any avalible attacks
						if (enemies->at(currentEnemyTurnIndex)->getEnemySkills()->size() > 0){
							ExecuteRandomEnemySkill(enemies->at(currentEnemyTurnIndex));
							attackConfirm = true;
						}
						else{
							NewEnemyTurn();
						}
						

						if (player->StatsManager()->getPlayerHP() <= 0){
							currentCombatState = Player_Lost;
						}
					}

				}
				else {					
					NewEnemyTurn();
				}

				
				break;

			case Combat_Over: 
					//after 1 sec switch back to normal game mode
					phaseSwitchPause += timeElapsed.asSeconds();
					if (phaseSwitchPause >= phaseSwitchPauseTime){
						currentCombatState = Combat_Phase_Over;
					}
					
				break;

			case Player_Lost:
				phaseSwitchPause += timeElapsed.asSeconds();

				//TODO: -optimize- hasDisplayedPlayerDied is a quick fix to avoid "You Died" being spammed.
				if (!hasDisplayedPlayerDied && phaseSwitchPause >= .5){
					gui->AddStatusText("You died.");
					hasDisplayedPlayerDied = true;
				}
				if (phaseSwitchPause >= phaseSwitchPauseTime + .5){
					currentCombatState = Game_Over;					
				}
				break;



			case Player_Debuff_Tick:
				//if the player has no debuffs the combat state switches instantly
				if (playerDebuffs.size() <= 0){
					gui->AddStatusText("Your move!");
					currentCombatState = Choosing_Action;
					break;
				}

				debuffTickTimer += timeElapsed.asSeconds();
				if (!debuffPhaseOver && debuffTickTimer >= .25){

					ExecuteEnemySkillEffect(playerDebuffs[debuffTickIndex].effect);
					playerDebuffs[debuffTickIndex].roundsToLast -= 1;
					//if the debuff durotation is over then it will be removed.
					if (playerDebuffs[debuffTickIndex].roundsToLast <= 0){
						//since the element is removed the debuffTickIndex is not increased.
						delete &playerDebuffs[debuffTickIndex];
						playerDebuffs.erase(playerDebuffs.begin() + debuffTickIndex);						
					}
					else{
						debuffTickIndex += 1;
					}
					
					//If there still are more debuffs that need to have their effect the timer
					//is reset for the next debuff.
					if (debuffTickIndex < playerDebuffs.size()){
						debuffTickTimer = 0;
					}
					//else the Player_Debuff_Tick phase is over.
					else {
						debuffTickTimer = 0;
						debuffTickIndex = 0;
						debuffPhaseOver = true;
					}
				}
				//if this phase is complete and another .25 seconds has passed 
				//the phase shift happens
				else if (debuffTickTimer >= .25){
					gui->AddStatusText("Your move!");
					debuffPhaseOver = false;
					currentCombatState = Choosing_Action;
					debuffTickTimer = 0;
				}
				
				//currentCombatState = Choosing_Action;
				break;
			default:
				break;
		}
		
		gui->DrawCombatPhase(window, &timeElapsed, player, enemies);		
	}

	if (phaseTransmissionAnimation){
		gui->TransitionAnimation(window, &timeElapsed);
		if (gui->isTransitionAnimationOver()){
			phaseTransmissionAnimation = false;			
		}
	}
}

/*
* <DESCRIPTION>
* Sets values for a new enemy to take it's turn.
*/
void GameCombatLoop::NewEnemyTurn(){
	currentEnemyTurnIndex += 1;
	currentEnemyTurnTime = 0;
	attackConfirm = false;
}


/*
* <DESCRIPTION>
* Executes a combat option the player decided on doing.
*/
void GameCombatLoop::ExecuteCombatOption(){
	switch (currentOption)
	{
		case CombatOptions::Attack:
			currentCombatState = CombatState::Choosing_Target;
			break;

		case CombatOptions::Skill:{
			if (player->SkillManager()->getPlayerSkills()->size() > 0){
				currentCombatState = Choosing_Skill;
			}
			else {
				gui->AddStatusText("You dont know any skills yet.");
			}
			
			break;
		}

		case CombatOptions::Item:
			gui->AddStatusText("Not Implemented Yet.");
			break;

		case CombatOptions::Run:
			gui->AddStatusText("Not Implemented Yet.");
			break;


		default:
			throw "Not a valid combat option was executed.";
			break;
	}
}


void GameCombatLoop::PlayerDealsDamage(vector<Enemy*> *enemies, int damage){
	currentCombatState = CombatState::Enemy_Turn;
	currentEnemyTurnTime = 0;

	enemies->at(targetIndex)->TakeDamage(damage);
	gui->AddEnemyCombatText(to_string(damage), targetIndex);

	//If the enemy died a new target index is set.
	if (!enemies->at(targetIndex)->IsAlive()){

		for (int i = 0; i < enemies->size(); ++i){
			if (enemies->at(i)->IsAlive()){
				targetIndex = i;
				break;
			}
			//Last iteration of the loop.
			if (i + 1 == enemies->size()){
				//All enemies are dead and the normal gameplay should resume.

				currentCombatState = CombatState::Combat_Over;
				gui->AddStatusText("You Won!");

				//grants the player win EXP
				for (auto &e : *enemies){
					player->StatsManager()->GainEXPPoints(e->getXPGrant());
				}
			}
		}
	}

}

//Any combat state that is where the player is in control this method should be called
//to see if the player want to go back to the base of choosing an action
void GameCombatLoop::PlayerCanGoBack(){
	//space key to go back 
	if (handleInput->CheckResetCombatStateInput()){
		currentCombatState = Choosing_Action;
	}
}

//executes a enemy skill
void GameCombatLoop::ExecuteRandomEnemySkill(Enemy *enemy){
	vector<int> usableSkillIndexes;
	for (int i = 0; i < enemy->getEnemySkills()->size(); ++i){
		if (enemy->getEnemySkills()->at(i)->CanCast()){
			usableSkillIndexes.push_back(i);
		}
	}
	srand(time(NULL));
	int randomIndex = rand() % usableSkillIndexes.size();

	PlayerTakesDamage(enemy->getEnemySkills()->at(randomIndex)->getSkillDamage(),
					enemy->getEnemyType(),
					enemy->getEnemySkills()->at(randomIndex)->getSkillName());

	//if the enemy skill is debuff orientated 
	if (enemy->getEnemySkills()->at(randomIndex)->isDebuff()){
		//Add debuff to the player or if the player is allready effected by 
		//the debuff it's durotation is reset.

		for (int i = 0; i < playerDebuffs.size(); ++i){
			//if the player if allready affected by this debuff then it will be refreshed and the 
			//the function will end.
			if (playerDebuffs[i].name == enemy->getEnemySkills()->at(randomIndex)->getSkillName()){
				//refreshes the durotation.
				playerDebuffs[i].roundsToLast = enemy->getEnemySkills()->at(randomIndex)->roundsToLast();
				return;
			}
		}
		//If the return is never called in the loop, the player is not affected
		//by this debuff and it gets added to the debuff list.
		Debuff debuff;
		debuff.effect = enemy->getEnemySkills()->at(randomIndex)->getEffect();
		debuff.roundsToLast = enemy->getEnemySkills()->at(randomIndex)->roundsToLast();
		debuff.name = enemy->getEnemySkills()->at(randomIndex)->getSkillName();
		playerDebuffs.push_back(debuff);

		
	}
	//Else just executes the skill special effect
	else{
		ExecuteEnemySkillEffect(enemy->getEnemySkills()->at(randomIndex)->getEffect());
	}
	//Displays text of the enemy attack
	
}

//TODO: add status text dispaly when called.
//executes a skill effect
void GameCombatLoop::ExecuteEnemySkillEffect(SkillEffect skillEffect){

	switch (skillEffect.consumes)
	{
		case Health:
			player->StatsManager()->playerHitPointsAffected(-skillEffect.amountConsumed);
			gui->AddStatusText("Player " + skillEffect.damageDescription + " for " + to_string(skillEffect.amountConsumed) + " Damage.");
			gui->AddPlayerCombatText(to_string(skillEffect.amountConsumed), player);
			break;

		case Stamina:
			player->StatsManager()->playerStaminaAffected(-skillEffect.amountConsumed);
			gui->AddStatusText("Player Stamina is " + skillEffect.damageDescription + " by " + to_string(skillEffect.amountConsumed) + " Points.");
			break;

		case Hunger:
			player->StatsManager()->playerHungerAffected(-skillEffect.amountConsumed);
			gui->AddStatusText("Player Hunger is " + skillEffect.damageDescription + " by " + to_string(skillEffect.amountConsumed) + " Points.");
			break;

		
		case Nothing_Consumed:
			return;
		default:
			throw "Stat to consume is not defined.";
	}
}

//deals damage to the player and calls gui method to display damage numbers
void GameCombatLoop::PlayerTakesDamage(float amount, EnemyType enemyType, string attackName){
	player->StatsManager()->playerHitPointsAffected(-amount);
	gui->AddPlayerCombatText(to_string(amount), player);
	gui->AddStatusCombatText(enemyType, attackName);
}