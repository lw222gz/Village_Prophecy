#pragma once
#include <string>
#include "SkillConsumeableStats.h"

using namespace std;

struct SkillEffect
{
	SkillConsumeableStats consumes;
	float amountConsumed;
	string damageDescription;
};

//Interface for game skills
class EnemySkill
{
public:
	virtual bool isDebuff() = 0;
	virtual string getSkillName() = 0;
	virtual float getSkillDamage() = 0;
	virtual bool CanCast() = 0;
	virtual SkillEffect getEffect() = 0;
	virtual int roundsToLast() = 0;
};
