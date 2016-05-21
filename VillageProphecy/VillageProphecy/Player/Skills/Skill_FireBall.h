#pragma once
#include "../../BaseClasses/Interfaces/IPlayerSkill.h"
#include "../PlayerStatsManager.h"

//Forward decleration
class Skill;
class PlayerStatsManager;

class Skill_FireBall : public IPlayerSkill
{

public:
	Skill_FireBall(PlayerStatsManager *_playerStats);
	~Skill_FireBall();

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

