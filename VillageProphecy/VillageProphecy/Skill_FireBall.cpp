#include "Skill_FireBall.h"

//Summary: A heavy single target damage skill with a hefty cost.

Skill_FireBall::Skill_FireBall(PlayerStatsManager *_playerStats) 
	: playerStats(_playerStats)
{
}


Skill_FireBall::~Skill_FireBall()
{
}


string Skill_FireBall::getSkillName(){
	return "Fireball";
}

string Skill_FireBall::getSkillDescripion(){
	return "Words of power are whipsered into your mind. You don't understand them but they slip out of your tongue and devestation is brought upon your enemies.";
}

int Skill_FireBall::getSkillDamage(){
	return playerStats->getPlayerAttackDamage() * 3;
}

SkillConsumeableStats Skill_FireBall::getStatConsumeType(){
	return SkillConsumeableStats::Stamina;
}

int Skill_FireBall::getConsumeAmount(){
	return 15;
}

void Skill_FireBall::ConsumeSkillStats(){
	playerStats->playerStaminaAffected(-getConsumeAmount());
}

//returns bool representing if the skill can be used
bool Skill_FireBall::CanCast(){
	return playerStats->getPlayerStamina() >= getConsumeAmount();
}