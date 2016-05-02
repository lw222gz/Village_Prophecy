#include "PlayerSkillManager.h"


PlayerSkillManager::PlayerSkillManager()
{
	
}


PlayerSkillManager::~PlayerSkillManager()
{
}


vector<Skill*>* PlayerSkillManager::getPlayerSkills(){
	return &playerSkills;
}

void PlayerSkillManager::LearnSkill(LevelEXPRequirement playerLevel, PlayerStatsManager *playerStats){
	//Add a skill to the playerskill vector denepning on the level gained
	switch (playerLevel)
	{
		case LEVEL_1:
			//Test to add many skills to be abel to chose between them
			playerSkills.push_back(new Skill_HeavyStrike(playerStats));
			break;

		case LEVEL_3:
			//Add fireball
			playerSkills.push_back(new Skill_FireBall(playerStats));
			break;
		case LEVEL_30:
			break;
		default:
			break;
	}
}