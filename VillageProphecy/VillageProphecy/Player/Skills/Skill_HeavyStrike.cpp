#include "Skill_HeavyStrike.h"

/*
* <DESCRIPTION>
* Constructor for the Skill_HeavyStrike class, sets the pointer to the PlayerStatsManage object
*
* @PARAMS
* _playerStats: pointer to the PlayerStatsManage object, used for settings the damage and consumption amounts for this skill.
*/
Skill_HeavyStrike::Skill_HeavyStrike(PlayerStatsManager *_playerStats)
	: playerStats(_playerStats)
{
}

Skill_HeavyStrike::~Skill_HeavyStrike()
{
}

/*
* @RETURNS
* returns string representing the description of this skill.
*/
string Skill_HeavyStrike::getSkillDescripion(){
	return "You execute a reckless swing that deals increased damage but backfires on you aswell.";
}

/*
* @RETURNS
* returns string representing the name of this skill.
*/
string Skill_HeavyStrike::getSkillName(){
	return "Heavy Strike";
}

/*
* @RETURNS
* returns integer representing the damage of this skill on use.
*/
int Skill_HeavyStrike::getSkillDamage(){
	return playerStats->getPlayerAttackDamage() * 2;
}

/*
* @RETURNS
* returns SkillConsumeableStats enum value representing the type of stat that is consumed by this skill
*/
SkillConsumeableStats Skill_HeavyStrike::getStatConsumeType(){
	return SkillConsumeableStats::Health;
}

/*
* @RETURNS
* returns integer representing the consumptions amount for the use of this skill.
*/
int Skill_HeavyStrike::getConsumeAmount(){
	return playerStats->getMaxPlayerHP() * .06;
}

/*
* <DESCRIPTION>
* Consumes the stats this skill requires.
*/
void Skill_HeavyStrike::ConsumeSkillStats(){
	playerStats->playerHitPointsAffected(-getConsumeAmount());
}

/*
* @RETURNS
* returns boolean representing if this skill can be used, true if it can be used otherwise false.
*/
bool Skill_HeavyStrike::CanCast(){
	return playerStats->getPlayerHP() > getConsumeAmount();
}