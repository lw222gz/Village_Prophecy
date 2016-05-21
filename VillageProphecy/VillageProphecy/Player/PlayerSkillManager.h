#pragma once
#include <vector>
#include "../Enums/LevelEXPRequirement.h"
#include "Skills\Skill_HeavyStrike.h"

//#include "IPlayerSkill.h"

class PlayerStatsManager;
class IPlayerSkill;
class Skill_FireBall;

class PlayerSkillManager
{
public:
	PlayerSkillManager();
	~PlayerSkillManager();

	vector<IPlayerSkill*> *getPlayerSkills();
	void LearnSkill(LevelEXPRequirement playerLevel, PlayerStatsManager *playerStats);
	bool hasPlayerLearnedFireball();
	bool canSetObjectOnFire();

private:
	vector<IPlayerSkill*> playerSkills;
	bool playerHasLearnedFireball = false;
	Skill_FireBall *fireballSkill = NULL;
};

