#include "PlayerStatsManager.h"

/*
* <DESCRIPTION>
* Constructor for the PlayerStatsManager class
* Sets Textures for player AP and contains all values for the player stats.
* Sets the players currentLevel to 0 as initialization.
*/
PlayerStatsManager::PlayerStatsManager(PlayerSkillManager *skillManager)
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

float PlayerStatsManager::getPlayerAttackDamage(){
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
float PlayerStatsManager::getPlayerHP(){
	return playerHitpoints;
}

/*
* @RETURNS
* returns the players hit point cap.
*/
float PlayerStatsManager::getMaxPlayerHP(){
	return MAX_HIT_POINTS;
}

/*
* @RETURNS
* returns the amount of hunger points the player has
*/
float PlayerStatsManager::getPlayerHunger(){
	return currentHunger;
}

/*
* @RETURNS
* returns the amount of mood points the player has
*/
float PlayerStatsManager::getPlayerMood(){
	return currentMood;
}

/*
* @RETURNS
* returns the amount of stamina points the player has
*/
float PlayerStatsManager::getPlayerStamina(){
	return currentStamina;
}

/*
* @RETURNS
* returnst the hunger point cap.
*/
float PlayerStatsManager::getPlayerMAXHunger(){
	return MAX_HUNGER_POINTS;
}

/*
* @RETURNS
* returns the mood points cap.
*/
float PlayerStatsManager::getPlayerMAXMood(){
	return MAX_MOOD_POINTS;
}

/*
* @RETURNS
* returnshe stamin point cap
*/
float PlayerStatsManager::getPlayerMAXStamina(){
	return MAX_STAMINA_POINTS;
}

/*
* <DESCRIPTION>
* Deals damage to the player
*
* @PARAMS
* amount: integer representing the amount of damage that is about to be dealt to the player.
*/
void PlayerStatsManager::damagePlayer(int amount){
	playerHitpoints -= amount;
	if (playerHitpoints <= 0){
		playerHitpoints = 0;
		//TODO: Player dies, game over.
	}
}

/*
* <DESCRIPTION>
* Affects the players hunger points negitivly or positivly depending on parameter.
*
* @PARAMS
* amount: integer representing the amount to be removed or added to the players hunger points
*/
void PlayerStatsManager::playerHungerAffected(float amount){
	currentHunger += amount;
	if (currentHunger < 0){
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
void PlayerStatsManager::playerMoodAffected(float amount){
	currentMood += amount;
	if (currentMood < 0){
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
void PlayerStatsManager::playerStaminaAffected(float amount){
	currentStamina += amount;
	if (currentStamina < 0){
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
			MAX_HIT_POINTS += 10;
			playerHitpoints += 10;

			ExperiencePointsToLevel = LEVEL_2;
			break;

		case LEVEL_1:
			currentLevel = LEVEL_2;
			MAX_HIT_POINTS += 25;
			playerHitpoints += 25;
			playerAttackDamage += 5;

			ExperiencePointsToLevel = LEVEL_3;
			break;

		case LEVEL_2:
			currentLevel = LEVEL_3;
			MAX_HIT_POINTS += 25;
			playerHitpoints += 25;
			playerAttackDamage += 5;

			ExperiencePointsToLevel = LEVEL_30;
			break;

		case LEVEL_3:
			currentLevel = LEVEL_30;
			ExperiencePointsToLevel = LEVEL_30;
			break;

		case LEVEL_30:
			//currentLevel = LEVEL_30;
			//Max level?
			break;
		default:
			break;
	}

	//If the player has already passed the next level limit aswell then the player will level up again.
	if (TotalExperiencePoints >= ExperiencePointsToLevel){
		PlayerLevelUp();
	}
}
