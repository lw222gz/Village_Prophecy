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
	float getPlayerHP();
	float getMaxPlayerHP();
	void damagePlayer(int amount);

	float getPlayerHunger();
	float getPlayerMood();
	float getPlayerStamina();

	float getPlayerMAXHunger();
	float getPlayerMAXMood();
	float getPlayerMAXStamina();

	void playerHungerAffected(float amount);
	void playerMoodAffected(float amount);
	void playerStaminaAffected(float amount);

	int getTotalExp();
	int getNextLevelExp();
	LevelEXPRequirement getCurrentLevel();

	
private:
	
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
	float currentStamina = MAX_STAMINA_POINTS;


	void PlayerLevelUp();
};

