#include "Skill_FireBall.h"

/*
* <DESCRIPTION>
* Constructor for the Skill_FireBall class, sets the pointer to the PlayerStatsManage object
*
* @PARAMS
* _playerStats: pointer to the PlayerStatsManage object, used for settings the damage and consumption amounts for this skill.
*/
Skill_FireBall::Skill_FireBall(PlayerStatsManager *_playerStats) 
	: playerStats(_playerStats)
{
}


Skill_FireBall::~Skill_FireBall()
{
}

/*
* @RETURNS
* returns string representing the name of this skill.
*/
string Skill_FireBall::getSkillName(){
	return "Fireball";
}

/*
* @RETURNS
* returns string representing the description of this skill.
*/
string Skill_FireBall::getSkillDescripion(){
	return "Words of power are whipsered into your mind. You don't understand them but they slip out of your tongue and devestation is brought upon your enemies.";
}

/*
* @RETURNS
* returns integer representing the damage of this skill on use.
*/
int Skill_FireBall::getSkillDamage(){
	return playerStats->getPlayerAttackDamage() * 3;
}

/*
* @RETURNS
* returns SkillConsumeableStats enum value representing the type of stat that is consumed by this skill
*/
SkillConsumeableStats Skill_FireBall::getStatConsumeType(){
	return SkillConsumeableStats::Stamina;
}

/*
* @RETURNS
* returns integer representing the consumptions amount for the use of this skill.
*/
int Skill_FireBall::getConsumeAmount(){
	return playerStats->getPlayerMAXStamina() * .15;
}

/*
* <DESCRIPTION>
* Consumes the stats this skill requires.
*/
void Skill_FireBall::ConsumeSkillStats(){
	playerStats->playerStaminaAffected(-getConsumeAmount());
}

/*
* @RETURNS
* returns boolean representing if this skill can be used, true if it can be used otherwise false.
*/
bool Skill_FireBall::CanCast(){
	return playerStats->getPlayerStamina() >= getConsumeAmount();
}