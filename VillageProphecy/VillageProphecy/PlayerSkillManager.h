#pragma once
#include <vector>
#include "LevelEXPRequirement.h"
#include "Skill_HeavyStrike.h"
#include "Skill_FireBall.h"
#include "Skill.h"



class PlayerStatsManager;

class PlayerSkillManager
{
public:
	PlayerSkillManager();
	~PlayerSkillManager();

	vector<Skill*>* getPlayerSkills();
	void LearnSkill(LevelEXPRequirement playerLevel, PlayerStatsManager *playerStats);

private:
	vector<Skill*> playerSkills;
};

