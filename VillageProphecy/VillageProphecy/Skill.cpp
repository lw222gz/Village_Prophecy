#include "Skill.h"


Skill::Skill(GameSkills _skillType) : skillType(_skillType)
{
	SetSkillValues();
}


Skill::~Skill()
{
}


void Skill::SetSkillValues(){

	switch (skillType)
	{
		case Heavy_Strike:
			skillName = "Heavy Strike";
			description = "A heavy strike that deals more damage but backfires damage to the player.";

			break;

		case Fireball_I:
			break;

		default:
			break;
	}
}