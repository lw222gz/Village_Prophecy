#pragma once
#include "Skill.h"
#include "PlayerStatsManager.h"

//forward decleration
class Skill;
class PlayerStatsManager;

class Skill_HeavyStrike : public Skill
{
public:
	Skill_HeavyStrike(PlayerStatsManager *playerStats);
	~Skill_HeavyStrike();

	string getSkillName();
	string getSkillDescripion();
	float getSkillDamage();
	SkillConsumeableStats getStatConsumeType();
	float getConsumeAmount();
	void ConsumeSkillStats();
	bool CanCast();
	

private:
	PlayerStatsManager *playerStats = NULL;
};

