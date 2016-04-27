#pragma once
#include <vector>
#include "LevelEXPRequirement.h"
#include "Skill_HeavyStrike.h"
#include "Skill.h"

using namespace std;

class PlayerSkillManager
{
public:
	PlayerSkillManager();
	~PlayerSkillManager();

	vector<Skill*>* getPlayerSkills();
	void LearnSkill(LevelEXPRequirement playerLevel);

private:
	vector<Skill*> playerSkills;
};

