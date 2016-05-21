#include "EnemySkill_NormalAttack.h"

//<summary>
//Normal attack of an enemy that just deals it's normal attack damage.

EnemySkill_NormalAttack::EnemySkill_NormalAttack(Enemy *e) : enemy(e)
{
	effect.consumes = Nothing_Consumed;
}


EnemySkill_NormalAttack::~EnemySkill_NormalAttack()
{
}


string EnemySkill_NormalAttack::getSkillName(){
	return "Normal Attack";
}

int EnemySkill_NormalAttack::getSkillDamage(){
	return enemy->getAttackDamage();
}

bool EnemySkill_NormalAttack::CanCast(){
	return true;
}

bool EnemySkill_NormalAttack::isDebuff(){
	return false;
}

int EnemySkill_NormalAttack::roundsToLast(){
	return 0;
}


SkillEffect EnemySkill_NormalAttack::getEffect(){
	return effect;
}