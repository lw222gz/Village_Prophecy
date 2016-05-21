#include "GameObject_Bed.h"

/*
* <DESCRIPTION>
* Constructor for the GameObject_Bed class.
* Sets base values.
*
* @PARAMS
* pos: Vector2f positon of the game object
* _BedTexture: pointer to the texture for the bed object.
*/
GameObject_Bed::GameObject_Bed(Vector2f pos, Texture *_BedTexture)
{
	objectSprite.setPosition(pos);
	objectSprite.setTexture(*_BedTexture);
	triggerType = Interactable;
}


GameObject_Bed::~GameObject_Bed()
{
}

/*
* @RETURNS
* returns the object sprite
*/
Sprite GameObject_Bed::getSprite(){
	return objectSprite;
}

/*
* @RETURNS
* returns the object trigger type
*/
TriggerType GameObject_Bed::getTriggerType(){
	return triggerType;
}

/*
* @RETURNS
* returns the object type
*/
GameObjectType GameObject_Bed::getObjectType(){
	return Bed;
}

//TODO: <optimize> plan is to remove this method from the base class.
MaterialList *GameObject_Bed::MaterialListManager(){
	return NULL;
}

//TODO: <optimize> plan is to remove this method from the base class.
void GameObject_Bed::completeConstruction(){
	return;
}

//TODO: <optimize> plan is to remove this method from the base class.
void GameObject_Bed::setOnFire(){
	return;
}

GameObjectType GameObject_Bed::getConsumptionType(){
	return GameObjectType::None;
}
