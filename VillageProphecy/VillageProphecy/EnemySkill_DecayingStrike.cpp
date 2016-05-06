#include "EnemySkill_DecayingStrike.h"

EnemySkill_DecayingStrike::EnemySkill_DecayingStrike(Enemy *e) : enemy(e)
{
}


EnemySkill_DecayingStrike::~EnemySkill_DecayingStrike()
{
}


string EnemySkill_DecayingStrike::getSkillName(){
	return "Decaying Strike";
}

float EnemySkill_DecayingStrike::getSkillDamage(){
	return enemy->getAttackDamage();
}

EnemySkillEffect EnemySkill_DecayingStrike::Effect(){
	return Decaying_Strike;
}

bool EnemySkill_DecayingStrike::CanCast(){
	return true;
}