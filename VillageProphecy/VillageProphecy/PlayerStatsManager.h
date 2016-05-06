#pragma once
#include <SFML/Graphics.hpp>
#include "LevelEXPRequirement.h"
#include "PlayerSkillManager.h"

//forward decleration
class PlayerSkillManager;

using namespace sf;

class PlayerStatsManager
{
public:
	PlayerStatsManager(PlayerSkillManager *skillManager);
	~PlayerStatsManager();

	void GainEXPPoints(int amount);

	void ResetAP();

	int getRemaningActionPoints();
	int getMaxActionsPoints();
	void ConsumeActionPoints(int amount);
	Sprite getAPSprite();
	Sprite getConsumedAPSprite();

	float getPlayerAttackDamage();

	void playerHitPointsAffected(float amount);
	float getPlayerHP();
	float getMaxPlayerHP();
	
	void playerHungerAffected(float amount);
	float getPlayerHunger();
	float getPlayerMAXHunger();

	void playerMoodAffected(float amount);
	float getPlayerMood();
	float getPlayerMAXMood();
	
	void playerStaminaAffected(float amount);
	float getPlayerStamina();
	float getPlayerMAXStamina();

	int getTotalExp();
	int getNextLevelExp();
	LevelEXPRequirement getCurrentLevel();

	
private:
	PlayerSkillManager *skillManager = NULL;
	const int ACTION_POINTS_MAX = 10;
	int actionPoints = 2;
	Texture APTexture;
	Texture consumedAPTexture;
	Sprite APSprite;
	Sprite consumedAPSprite;

	int TotalExperiencePoints = 0;
	LevelEXPRequirement currentLevel = LEVEL_0;
	LevelEXPRequirement ExperiencePointsToLevel = LevelEXPRequirement::LEVEL_1;

	float playerAttackDamage = 10;

	float MAX_HIT_POINTS = 100;
	float playerHitpoints = MAX_HIT_POINTS;

	const float MAX_HUNGER_POINTS = 100;
	const float MAX_MOOD_POINTS = 100;
	const float MAX_STAMINA_POINTS = 100;

	float currentHunger = MAX_HUNGER_POINTS;
	float currentMood = MAX_MOOD_POINTS;
	float currentStamina = 10;


	void PlayerLevelUp();
};

