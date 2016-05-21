#include "GameObject_HealingStation.h"

//<summary>
//Object that consumes 1 wood game item when used and restores a small amount of health to the player

GameObject_HealingStation::GameObject_HealingStation(Vector2f pos, Texture *_HealingStationTexture)
{
	objectSprite.setPosition(pos);
	objectSprite.setTexture(*_HealingStationTexture);
	triggerType = Usable;
}


GameObject_HealingStation::~GameObject_HealingStation()
{
}

Sprite GameObject_HealingStation::getSprite(){
	return objectSprite;
}
TriggerType GameObject_HealingStation::getTriggerType(){
	return triggerType;
}
GameObjectType GameObject_HealingStation::getObjectType(){
	return HealingStation;
}

GameObjectType GameObject_HealingStation::getConsumptionType(){
	return Tree;
}

MaterialList *GameObject_HealingStation::MaterialListManager(){
	return NULL;
}
void GameObject_HealingStation::completeConstruction(){
	return;
}
void GameObject_HealingStation::setOnFire(){
	return;
}