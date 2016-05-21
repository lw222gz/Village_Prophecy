#pragma once
/*
* Enum is used in several classes, all classes who use it have it linked in their .h
*/
enum TriggerType
{
	Loot = 400,
	Harvest,
	Build,
	Interactable,
	Usable,
	Set_On_Fire,
	No_Action
};