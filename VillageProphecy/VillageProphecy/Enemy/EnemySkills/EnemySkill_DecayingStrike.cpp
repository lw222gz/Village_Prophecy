#include "EnemySkill_DecayingStrike.h"

//<summary>
//A strike that deals abit lower damage then normal attack but drains the players stamina

EnemySkill_DecayingStrike::EnemySkill_DecayingStrike(Enemy *e) : enemy(e)
{
	effect.consumes = Stamina;
	effect.amountConsumed = 10;
	effect.damageDescription = "Drained";
}


EnemySkill_DecayingStrike::~EnemySkill_DecayingStrike()
{
}


string EnemySkill_DecayingStrike::getSkillName(){
	return "Decaying Strike";
}

int EnemySkill_DecayingStrike::getSkillDamage(){
	return enemy->getAttackDamage() * .8;
}

SkillEffect EnemySkill_DecayingStrike::getEffect(){
	return effect;
}

int EnemySkill_DecayingStrike::roundsToLast(){
	return 0;
}

bool EnemySkill_DecayingStrike::CanCast(){
	return true;
}

bool EnemySkill_DecayingStrike::isDebuff(){
	return false;
}