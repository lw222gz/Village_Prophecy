#include "EnemySkill_BloodyStrike.h"

//<summary> 
//An attack that deals no initial damage but deals damage to the target each round for 5 rounds.

EnemySkill_BloodyStrike::EnemySkill_BloodyStrike(Enemy *e) : enemy(e)
{
	effect.consumes = Health;
	effect.amountConsumed = (int)round((float)enemy->getAttackDamage() * .3f);
	effect.damageDescription = "Bleeds";
}


EnemySkill_BloodyStrike::~EnemySkill_BloodyStrike()
{
}



string EnemySkill_BloodyStrike::getSkillName(){
	return "Bloody Strike";
}

int EnemySkill_BloodyStrike::getSkillDamage(){
	return 0;
}

int EnemySkill_BloodyStrike::roundsToLast(){
	return 5;
}

//TODO: add a CD
bool EnemySkill_BloodyStrike::CanCast(){
	return true;
}

bool EnemySkill_BloodyStrike::isDebuff(){
	return true;
}

SkillEffect EnemySkill_BloodyStrike::getEffect(){
	return effect;
}
