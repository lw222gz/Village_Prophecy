#include "EnemySkill_BloodyStrike.h"

//<summary> 
//A Debuff attack that deals damage over a couple of rounds.

EnemySkill_BloodyStrike::EnemySkill_BloodyStrike(Enemy *e) : enemy(e)
{
	effect.consumes = Health;
	effect.amountConsumed = enemy->getAttackDamage() * .3;
	effect.damageDescription = "Bleeds";
}


EnemySkill_BloodyStrike::~EnemySkill_BloodyStrike()
{
}



string EnemySkill_BloodyStrike::getSkillName(){
	return "Bloody Strike";
}

float EnemySkill_BloodyStrike::getSkillDamage(){
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
