#include "Skill_HeavyStrike.h"


Skill_HeavyStrike::Skill_HeavyStrike(PlayerStatsManager *_playerStats)
	: playerStats(_playerStats)
{
}

Skill_HeavyStrike::~Skill_HeavyStrike()
{
}

string Skill_HeavyStrike::getSkillDescripion(){
	return "You execute a reckless swing that deals increased damage but backfires on you aswell.";
}
string Skill_HeavyStrike::getSkillName(){
	return "Heavy Strike";
}

float Skill_HeavyStrike::getSkillDamage(){
	return playerStats->getPlayerAttackDamage() * 2;
}

SkillConsumeableStats Skill_HeavyStrike::getStatConsumeType(){
	return SkillConsumeableStats::Health;
}

float Skill_HeavyStrike::getConsumeAmount(){
	return playerStats->getMaxPlayerHP() / 10;
}