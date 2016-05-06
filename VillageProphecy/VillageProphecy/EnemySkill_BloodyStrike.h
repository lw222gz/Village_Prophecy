#pragma once
#include "EnemySkill.h"
#include "Enemy.h"
//forward decleration
class EnemySkill;
class Enemy;

class EnemySkill_BloodyStrike : public EnemySkill
{
public:
	EnemySkill_BloodyStrike(Enemy *e);
	~EnemySkill_BloodyStrike();

	string getSkillName();
	float getSkillDamage();
	bool CanCast();
	EnemySkillEffect Effect();

private:
	Enemy *enemy;
};

