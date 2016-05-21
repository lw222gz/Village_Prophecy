#pragma once
#include <SFML/Graphics.hpp>
#include "../Enums/LevelEXPRequirement.h"
#include "PlayerSkillManager.h"

//forward decleration
class PlayerSkillManager;

using namespace sf;

class PlayerStatsManager
{
public:
	PlayerStatsManager(PlayerSkillManager *skillManager, Texture *APTexture, Texture *consumedAPTexture);
	~PlayerStatsManager();

	void GainEXPPoints(int amount);

	void ResetAP();

	int getRemaningActionPoints();
	int getMaxActionsPoints();
	void ConsumeActionPoints(int amount);
	Sprite getAPSprite();
	Sprite getConsumedAPSprite();

	int getPlayerAttackDamage();

	void playerHitPointsAffected(int amount);
	int getPlayerHP();
	int getMaxPlayerHP();
	
	void playerHungerAffected(int amount);
	int getPlayerHunger();
	int getPlayerMAXHunger();

	void playerMoodAffected(int amount);
	int getPlayerMood();
	int getPlayerMAXMood();
	
	void playerStaminaAffected(int amount);
	int getPlayerStamina();
	int getPlayerMAXStamina();

	int getTotalExp();
	int getNextLevelExp();
	LevelEXPRequirement getCurrentLevel();

	
private:
	PlayerSkillManager *skillManager = NULL;
	const int ACTION_POINTS_MAX = 10;
	int actionPoints = 8;
	Texture APTexture;
	Texture consumedAPTexture;
	Sprite APSprite;
	Sprite consumedAPSprite;

	int TotalExperiencePoints = 0;
	LevelEXPRequirement currentLevel = LEVEL_0;
	LevelEXPRequirement ExperiencePointsToLevel = LevelEXPRequirement::LEVEL_1;

	int playerAttackDamage = 10;

	int MAX_HIT_POINTS = 100;
	int playerHitpoints = MAX_HIT_POINTS;

	const int MAX_HUNGER_POINTS = 100;
	const int MAX_MOOD_POINTS = 100;
	const int MAX_STAMINA_POINTS = 100;

	int currentHunger = MAX_HUNGER_POINTS;
	int currentMood = MAX_MOOD_POINTS;
	int currentStamina = MAX_STAMINA_POINTS;


	void PlayerLevelUp();
};

