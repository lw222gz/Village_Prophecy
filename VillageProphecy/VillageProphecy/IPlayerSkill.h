#pragma once
#include "SkillConsumeableStats.h"
#include <string>

using namespace std;

//Interface for game skills
class IPlayerSkill
{
public:
	virtual string getSkillName() = 0;
	virtual string getSkillDescripion() = 0;
	virtual int getSkillDamage() = 0;
	virtual SkillConsumeableStats getStatConsumeType() = 0;
	virtual int getConsumeAmount() = 0;
	virtual bool CanCast() = 0;
	virtual void ConsumeSkillStats() = 0;
};

