#pragma once
#include "Skill.h"
#include "PlayerStatsManager.h"

//Forward decleration
class Skill;
class PlayerStatsManager;

class Skill_FireBall : public Skill
{

public:
	Skill_FireBall(PlayerStatsManager *_playerStats);
	~Skill_FireBall();

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

