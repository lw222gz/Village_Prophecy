#pragma once
#include "IPlayerSkill.h"
#include "PlayerStatsManager.h"

//forward decleration
class Skill;
class PlayerStatsManager;

class Skill_HeavyStrike : public IPlayerSkill
{
public:
	Skill_HeavyStrike(PlayerStatsManager *playerStats);
	~Skill_HeavyStrike();

	string getSkillName();
	string getSkillDescripion();
	int getSkillDamage();
	SkillConsumeableStats getStatConsumeType();
	int getConsumeAmount();
	void ConsumeSkillStats();
	bool CanCast();
	

private:
	PlayerStatsManager *playerStats = NULL;
};

