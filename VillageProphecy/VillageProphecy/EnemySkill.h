#pragma once
#include <string>
#include "EnemySkillEffect.h"

using namespace std;

//Interface for game skills
class EnemySkill
{
public:
	virtual string getSkillName() = 0;
	virtual float getSkillDamage() = 0;
	virtual bool CanCast() = 0;
	virtual EnemySkillEffect Effect() = 0;
};
