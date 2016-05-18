#include "PlayerSkillManager.h"
#include "Skill_FireBall.h"


PlayerSkillManager::PlayerSkillManager()
{
	
}


PlayerSkillManager::~PlayerSkillManager()
{
}

/*
* <DESCRIPTION>
* Since fireball is a skill that can be used outside of combat this method checks if
* the player has learned that skill.
*
* @RETURNS
* returns boolean, true if the player has learend the skill Fireball, otherwise false.
*/
bool PlayerSkillManager::hasPlayerLearnedFireball(){
	return playerHasLearnedFireball;
}

/*
* <DESCRIPTION>
* Since fireball is a skill that can be used outside of combat this method checks if
* the player can cast the skill and if so consumes the resources to do so.
* This method is only used when the player is OUTSIDE OF COMBAT.
*
* @RETURNS
* retuns boolean representing if the fireball skill was used or not, true if it was used, otherwise false.
*/
bool PlayerSkillManager::canSetObjectOnFire(){
	if (fireballSkill->CanCast()){

		fireballSkill->ConsumeSkillStats();
		return true;
	}
	return false;
}

/*
* @RETURNS
* returns a vecotr contaning all of the skills the player has learned.
*/
vector<IPlayerSkill*>* PlayerSkillManager::getPlayerSkills(){
	return &playerSkills;
}

/*
* <DESCRIPTION>
* Whenever the player levels this method is called to give any skills the player
* should learn at the characters current level.
*
* @PARAMS
* playerLevel: LevelEXPRequirement enum value representing the level the player just aquired.
* playerStats: Pointer to the players PlayerStatsManager to set damage values for the attacks.
*/
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