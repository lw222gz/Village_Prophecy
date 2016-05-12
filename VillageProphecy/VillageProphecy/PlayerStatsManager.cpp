#include "PlayerStatsManager.h"

/*
* <DESCRIPTION>
* Constructor for the PlayerStatsManager class
* Sets Textures for player AP and contains all values for the player stats.
* Sets the players currentLevel to 0 as initialization.
*/
PlayerStatsManager::PlayerStatsManager(PlayerSkillManager *_skillManager) : skillManager(_skillManager)
{
	currentLevel = LEVEL_0;

	if (!APTexture.loadFromFile("Textures/PHActionPoint.png")){
		throw "TEXTURE LOAD ERROR: Action point texture did not load correctly.";
	}
	APSprite.setTexture(APTexture);

	if (!consumedAPTexture.loadFromFile("Textures/PHConsumedActionPoint.png")){
		throw "TEXTURE LOAD ERROR: Consumed Action point texture did not load correctly.";
	}
	consumedAPSprite.setTexture(consumedAPTexture);
}


PlayerStatsManager::~PlayerStatsManager()
{
}



/*
* <DESCRIPTION>
* Rewards the player with Experience points.
*
* @PARAMS
* amount: integer representing the amount of Experience points that is given to the player.
*/
void PlayerStatsManager::GainEXPPoints(int amount){
	TotalExperiencePoints += amount;
	if (TotalExperiencePoints >= ExperiencePointsToLevel){
		PlayerLevelUp();
	}
}

int PlayerStatsManager::getPlayerAttackDamage(){
	return playerAttackDamage;
}

/*
* <DESCRIPTION>
* Resets the Action points to it's cap.
*/
void PlayerStatsManager::ResetAP(){
	actionPoints = ACTION_POINTS_MAX;
}

/*
* @RETURNS
* returns the remaning AP for the day.
*/
int PlayerStatsManager::getRemaningActionPoints(){
	return actionPoints;
}

/*
* <DESCRIPTION>
* Removes action points from the player
*
* @PARAMS
* amount: integer representing the amount to be removed.
*/
void PlayerStatsManager::ConsumeActionPoints(int amount){
	actionPoints -= amount;
}

/*
* @RETURNS
* returns sprite for an Action Point.
*/
Sprite PlayerStatsManager::getAPSprite(){
	return APSprite;

}

/*
* @RETURNS
* returns the sprite for a consumed Action point
*/
Sprite PlayerStatsManager::getConsumedAPSprite(){
	return consumedAPSprite;
}

/*
* @RETURNS
* returns max amount of action points.
*/
int PlayerStatsManager::getMaxActionsPoints(){
	return ACTION_POINTS_MAX;
}

/*
* @RETURNS
* returns the players hit points.
*/
int PlayerStatsManager::getPlayerHP(){
	return playerHitpoints;
}

/*
* @RETURNS
* returns the players hit point cap.
*/
int PlayerStatsManager::getMaxPlayerHP(){
	return MAX_HIT_POINTS;
}

/*
* @RETURNS
* returns the amount of hunger points the player has
*/
int PlayerStatsManager::getPlayerHunger(){
	return currentHunger;
}

/*
* @RETURNS
* returns the amount of mood points the player has
*/
int PlayerStatsManager::getPlayerMood(){
	return currentMood;
}

/*
* @RETURNS
* returns the amount of stamina points the player has
*/
int PlayerStatsManager::getPlayerStamina(){
	return currentStamina;
}

/*
* @RETURNS
* returnst the hunger point cap.
*/
int PlayerStatsManager::getPlayerMAXHunger(){
	return MAX_HUNGER_POINTS;
}

/*
* @RETURNS
* returns the mood points cap.
*/
int PlayerStatsManager::getPlayerMAXMood(){
	return MAX_MOOD_POINTS;
}

/*
* @RETURNS
* returnshe stamin point cap
*/
int PlayerStatsManager::getPlayerMAXStamina(){
	return MAX_STAMINA_POINTS;
}

/*
* <DESCRIPTION>
* Affects the player hitpoints
*
* @PARAMS
* amount: integer representing the amount of health that is gonna be added to the players
* current hit points or the amount that is to be removed from the players hitpoints
*/
void PlayerStatsManager::playerHitPointsAffected(int amount){
	playerHitpoints += amount;
	if (playerHitpoints > MAX_HIT_POINTS){
		playerHitpoints = MAX_HIT_POINTS;
	}
	else if (playerHitpoints <= 0){
		playerHitpoints = 0;
		//TODO: player died and game is over.
	}
}

/*
* <DESCRIPTION>
* Affects the players hunger points negitivly or positivly depending on parameter.
*
* @PARAMS
* amount: integer representing the amount to be removed or added to the players hunger points
*/
void PlayerStatsManager::playerHungerAffected(int amount){
	currentHunger += amount;
	if (currentHunger > MAX_HUNGER_POINTS){
		currentHunger = MAX_HUNGER_POINTS;
	}
	else if (currentHunger < 0){
		currentHunger = 0;
	}
}

/*
* <DESCRIPTION>
* Affects the players mood points negitivly or positivly depending on parameter.
*
* @PARAMS
* amount: integer representing the amount to be removed or added to the players mood points
*/
void PlayerStatsManager::playerMoodAffected(int amount){
	currentMood += amount;
	if (currentMood > MAX_MOOD_POINTS){
		currentMood = MAX_MOOD_POINTS;
	}
	else if (currentMood < 0){
		currentMood = 0;
	}
}

/*
* <DESCRIPTION>
* Affects the players stamina points negitivly or positivly depending on parameter.
*
* @PARAMS
* amount: integer representing the amount to be removed or added to the players stamina points
*/
void PlayerStatsManager::playerStaminaAffected(int amount){
	currentStamina += amount;
	if (currentStamina > MAX_STAMINA_POINTS){
		currentStamina = MAX_STAMINA_POINTS;
	}
	else if (currentStamina < 0){
		currentStamina = 0;
	}
}

/*
* @RETURNS
* returns the players current amount of EXP points
*/
int PlayerStatsManager::getTotalExp(){
	return TotalExperiencePoints;
}

/*
* @RETURNS
* returns the amount of EXP points the player needs to reach to get to the next level
*/
int PlayerStatsManager::getNextLevelExp(){
	return ExperiencePointsToLevel;
}

/*
* @RETURNS
* returns a LevelEXPRequirement representing the players current level.
*/
LevelEXPRequirement PlayerStatsManager::getCurrentLevel(){
	return currentLevel;
}

/*
* <DESCRIPTION>
* Levels up the player to the next level and sets cap for the new next level.
* If the player has enough EXP points to reach a new level again then this method will call itself.
*/
void PlayerStatsManager::PlayerLevelUp(){
	switch (currentLevel)
	{
		case LEVEL_0:
			currentLevel = LEVEL_1;
			ExperiencePointsToLevel = LEVEL_2;

			MAX_HIT_POINTS += 10;
			playerHitpoints += 10;
			break;

		case LEVEL_1:
			currentLevel = LEVEL_2;
			ExperiencePointsToLevel = LEVEL_3;

			MAX_HIT_POINTS += 25;
			playerHitpoints += 25;
			playerAttackDamage += 5;
			break;

		case LEVEL_2:
			currentLevel = LEVEL_3;
			ExperiencePointsToLevel = LEVEL_4;

			MAX_HIT_POINTS += 25;
			playerHitpoints += 25;
			playerAttackDamage += 5;			
			break;

		case LEVEL_3:
			currentLevel = LEVEL_4;
			ExperiencePointsToLevel = LEVEL_5;

			MAX_HIT_POINTS += 35;
			playerHitpoints += 35;
			break;

		case LEVEL_4:
			currentLevel = LEVEL_5;
			ExperiencePointsToLevel = LEVEL_6;

			MAX_HIT_POINTS += 35;
			playerHitpoints += 35;
			playerAttackDamage += 10;
			break;

		case LEVEL_5:
			currentLevel = LEVEL_6;
			ExperiencePointsToLevel = LEVEL_MAX;

			MAX_HIT_POINTS += 35;
			playerHitpoints += 35;
			break;

		case LEVEL_MAX:
			playerHitpoints = 999;
			playerAttackDamage = 999;
			//currentLevel = LEVEL_30;
			//Max level?
			break;
		default:
			break;
	}

	skillManager->LearnSkill(currentLevel, this);

	//If the player has already passed the next level limit aswell then the player will level up again.
	if (TotalExperiencePoints >= ExperiencePointsToLevel){
		PlayerLevelUp();
	}
}
