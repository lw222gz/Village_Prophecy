#include "EnemySkill_NormalAttack.h"


EnemySkill_NormalAttack::EnemySkill_NormalAttack(Enemy *e) : enemy(e)
{
}


EnemySkill_NormalAttack::~EnemySkill_NormalAttack()
{
}


string EnemySkill_NormalAttack::getSkillName(){
	return "Normal Attack";
}

float EnemySkill_NormalAttack::getSkillDamage(){
	return enemy->getAttackDamage();
}

bool EnemySkill_NormalAttack::CanCast(){
	return true;
}

EnemySkillEffect EnemySkill_NormalAttack::Effect(){
	return Normal_Attack;
}