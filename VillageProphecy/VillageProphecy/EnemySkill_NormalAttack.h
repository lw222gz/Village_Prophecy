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
	EnemySkillEffect Effect();

private:
	Enemy *enemy;
};

