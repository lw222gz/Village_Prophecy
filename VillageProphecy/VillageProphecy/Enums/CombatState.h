#pragma once
/*
* Enum is used in several classes, all classes who use it have it linked in their .h
*/
enum CombatState
{
	Choosing_Action = 100,
	Choosing_Skill,
	Choosing_Skill_Target,
	Choosing_Target,
	Player_Debuff_Tick,
	Enemy_Turn,
	Combat_Over,
	Combat_Phase_Over,
	Player_Lost,
	Game_Over
};