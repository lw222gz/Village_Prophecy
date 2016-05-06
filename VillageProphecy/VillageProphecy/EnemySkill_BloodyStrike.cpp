#include "EnemySkill_BloodyStrike.h"

EnemySkill_BloodyStrike::EnemySkill_BloodyStrike(Enemy *e) : enemy(e)
{
}


EnemySkill_BloodyStrike::~EnemySkill_BloodyStrike()
{
}


string EnemySkill_BloodyStrike::getSkillName(){
	return "Bloody Strike";
}

float EnemySkill_BloodyStrike::getSkillDamage(){
	return enemy->getAttackDamage() * 0.3;
}

//TODO: add a CD
bool EnemySkill_BloodyStrike::CanCast(){
	return true;
}

EnemySkillEffect EnemySkill_BloodyStrike::Effect(){
	return Bloody_Strike;
}
