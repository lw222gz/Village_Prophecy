#pragma once
#include "EnemySkill.h"
#include "Enemy.h"
//forward decleration
class EnemySkill;
class Enemy;

class EnemySkill_DecayingStrike : public EnemySkill
{
public:
	EnemySkill_DecayingStrike(Enemy *e);
	~EnemySkill_DecayingStrike();

	string getSkillName();
	float getSkillDamage();
	SkillEffect getEffect();
	bool CanCast();
	int roundsToLast();
	bool isDebuff();

private:
	Enemy *enemy = NULL;
	SkillEffect effect;
};

