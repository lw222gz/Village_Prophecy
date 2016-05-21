#include "GameObject_FirePlace.h"

/*
* <DESCRIPTION>
* Constructor for the GameObject_FirePlace class.
* Sets base values.
*
* @PARAMS
* pos: Vector2f positon of the game object
* _FirePlaceTexture: pointer to the texture for the fireplace object.
* _BurningFirePlaceTexture: pointer to the texture for a burning fireplace object.
*/
GameObject_FirePlace::GameObject_FirePlace(Vector2f pos, Texture *_FirePlaceTexture, Texture *_BurningFirePlaceTexture) 
	: FirePlaceTexture(*_FirePlaceTexture), BurningFirePlaceTexture(*_BurningFirePlaceTexture)
{
	objectSprite.setPosition(pos);
	objectSprite.setTexture(FirePlaceTexture);
	triggerType = Build;

	//
	materialList = new MaterialList(GameObjectType::Fireplace);
	objectSprite.setColor(Color(255, 255, 255, 128));
	//firePlaceDaysLasted = 0;
}


GameObject_FirePlace::~GameObject_FirePlace()
{
}

/*
* @RETURNS
* returns the object sprite
*/
Sprite GameObject_FirePlace::getSprite(){
	return objectSprite;
}

/*
* @RETURNS
* returns the object trigger type
*/
TriggerType GameObject_FirePlace::getTriggerType(){
	return triggerType;
}

/*
* @RETURNS
* returns the object type
*/
GameObjectType GameObject_FirePlace::getObjectType(){
	return type;
}

GameObjectType GameObject_FirePlace::getConsumptionType(){
	return None;
}

/*
* @RETURNS
* returns the material list for the construction of this object.
*/
MaterialList *GameObject_FirePlace::MaterialListManager(){
	return materialList;
}


/*
* <DESCRIPTION>
* This method is called each game night the fire still burns, 
* the fire will burn out after firePlaceLifeTime days has passed since 
* the day it was put on fire. When it burns out the firepalce will need to be reconstructed.
*/
void GameObject_FirePlace::firePlaceBurnOut(){
	firePlaceDaysLasted += 1;
	//
	if (firePlaceDaysLasted >= firePlaceLifeTime){
		//set textures
		objectSprite.setTexture(FirePlaceTexture);
		triggerType = TriggerType::Build;
		type = Fireplace;
		materialList = new MaterialList(type);
		objectSprite.setColor(Color(255, 255, 255, 128));
		firePlaceDaysLasted = 0;
	}
}



/*
* <DESCRIPTION>
* Sets the fireplace on fire
*/
void GameObject_FirePlace::setOnFire(){
	objectSprite.setTexture(BurningFirePlaceTexture);
	type = Burning_Fireplace;
	triggerType = No_Action;
}


/*
* <DESCRIPTION>
* Completes the construction of the fireplace
*/
void GameObject_FirePlace::completeConstruction(){
	delete materialList;
	objectSprite.setColor(Color(255, 255, 255, 255));

	triggerType = TriggerType::Set_On_Fire;	
}