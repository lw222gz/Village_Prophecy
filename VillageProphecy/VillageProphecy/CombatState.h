#pragma once
/*
* Enum is used in several classes, all classes who use it have it linked in their .h
*/
enum CombatState
{
	Choosing_Action = 100,
	Choosing_Target,
	Enemy_Turn,
	Combat_Over
};