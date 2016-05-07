#pragma once
#include "EnemySkill.h"
#include "Enemy.h"
//forward decleration
class EnemySkill;
class Enemy;

class EnemySkill_NormalAttack : public EnemySkill
{
public:
	EnemySkill_NormalAttack(Enemy *e);
	~EnemySkill_NormalAttack();

	string getSkillName();
	float getSkillDamage();
	bool CanCast();
	SkillEffect getEffect();
	int roundsToLast();
	bool isDebuff();

private:
	Enemy *enemy;
	SkillEffect effect;
};

