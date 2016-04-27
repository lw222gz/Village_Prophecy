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

void PlayerSkillManager::LearnSkill(LevelEXPRequirement playerLevel){
	//Add a skill to the playerskill vector denepning on the level gained
	switch (playerLevel)
	{
		case LEVEL_2:
			//playerSkills.push_back(new Skill_HeavyStrike());

			break;
		case LEVEL_3:
			break;
		case LEVEL_30:
			break;
		default:
			break;
	}
}