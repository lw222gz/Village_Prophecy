#pragma once
#include "SkillConsumeableStats.h"
#include <string>

using namespace std;

//Interface for game skills
class Skill
{
public:
	virtual string getSkillName() = 0;
	virtual string getSkillDescripion() = 0;
	virtual float getSkillDamage() = 0;
	virtual SkillConsumeableStats getStatConsumeType() = 0;
	virtual float getConsumeAmount() = 0;
};

