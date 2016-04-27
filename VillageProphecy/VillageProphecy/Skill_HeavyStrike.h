#pragma once
#include "Skill.h"
#include "PlayerStatsManager.h"

//forward decleration
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
	

private:
	PlayerStatsManager *playerStats = NULL;
};

