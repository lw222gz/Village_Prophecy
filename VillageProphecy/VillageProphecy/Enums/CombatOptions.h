#pragma once
/*
* Enum is used in several classes, all classes who use it have it linked in their .h
* RULE: First and last must be defined to ease up if's and loops for this enum.
* First being the lowest valued and Last then being the highest valued.
*/
enum CombatOptions
{
	Attack = 0,
	Skill,
	Item,
	Run,

	First = Attack,
	Last = Run
};