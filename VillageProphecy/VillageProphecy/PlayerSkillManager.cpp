#include "PlayerSkillManager.h"
#include "Skill_FireBall.h"


PlayerSkillManager::PlayerSkillManager()
{
	
}


PlayerSkillManager::~PlayerSkillManager()
{
}

bool PlayerSkillManager::hasPlayerLearnedFireball(){
	return playerHasLearnedFireball;
}

//returns true if the player can set an object on fire, otherwise false.
bool PlayerSkillManager::canSetObjectOnFire(){
	if (fireballSkill->CanCast()){

		fireballSkill->ConsumeSkillStats();
		return true;
	}
	return false;
}

vector<IPlayerSkill*>* PlayerSkillManager::getPlayerSkills(){
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
			//TODO: optimize
			//since fireball can have effects outside of combat it needs to be abel to be called
			//at any point
			fireballSkill = new Skill_FireBall(playerStats);
			playerSkills.push_back(fireballSkill);
			playerHasLearnedFireball = true;
			break;

		case LEVEL_5:
			//TODO: learn cleave
			break;

		case LEVEL_MAX:
			break;

		default:
			break;
	}
}