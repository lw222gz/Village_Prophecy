#include "GameObject.h"

/*
* <DESCRIPTION>
* Constructor for the GameObject class
*
* @PARAMS
* objectType: an enum value of thee GameObjectType enum that represents what kind of object that is being created
* pos: a Vector2f representing the position off the object.
*/
GameObject::GameObject(GameObjectType objectType, Vector2f pos) : type(objectType)
{
	objectSprite.setPosition(pos);
	setObjectSprite();
}


GameObject::~GameObject()
{
}

/*
* @RETURNS
* returns the game objects GameObjectType
*/
GameObjectType GameObject::getObjectType(){
	return type;
}

/*
* @RETURNS
* returns the sprite of the game object
*/
Sprite GameObject::getSprite(){
	return objectSprite;
}

/*
* @RETURNS
* returns the MaterialList object IF the gameobject is buildable
*/
MaterialList* GameObject::MaterialListManager(){
	//TODO: what if this gets called wrong and materialList is null?
	return materialList;
}

/*
* <DESCRIPTION>
* Checks collision between the objects position and the players position.
* TriggerRange is included.
*
* @PARAMS
* p: pointer to the Player game object
*
*/
bool GameObject::isTriggerd(Player *p){
	if (p->getPosition().x + p->getSize().x >= objectSprite.getPosition().x - triggerRange &&
		p->getPosition().x <= objectSprite.getPosition().x + objectTexture.getSize().x + triggerRange &&
		p->getPosition().y + p->getSize().y >= objectSprite.getPosition().y - triggerRange &&
		p->getPosition().y <= objectSprite.getPosition().y + objectTexture.getSize().y + triggerRange){
		//TODO: add Y collosion
		return true;
	}
	else{
		return false;
	}
}

/*
* @RETURNS
* returns a TriggerType enum value that represents the trigger type for the game object
*/
TriggerType GameObject::getTriggerType(){
	return triggerType;
}



/*
* <DESCRIPTION>
* sets the values and sprite for the gameobject depending on it's type.
*/
void GameObject::setObjectSprite(){

	switch (type){

		case GameObjectType::Tree:
			if (!objectTexture.loadFromFile("Textures/WoodObject.png")){
				throw "Game object Wood textures did not load correctly.";
			}
			triggerType = TriggerType::Harvest;
			break;

		case GameObjectType::Fireplace:
			if (!objectTexture.loadFromFile("Textures/FirePlace.png")){
				throw "TEXTURE LOAD ERROR: Fire place texture did not load correctly";
			}
			triggerType = TriggerType::Build;
			materialList = new MaterialList(type);
			objectSprite.setColor(Color(255,255,255,128));
				
			break;


		case GameObjectType::Bed:
			if (!objectTexture.loadFromFile("Textures/Bed.png")){
				throw "TEXTURE LOAD ERROR: Bed texture did not load correctly.";
			}
			triggerType = TriggerType::Interactable;

			break;

		default:
			//Throw err if the game object type is not defined
			throw "GAME_OBJECT_ERROR: Not a valid gameobject type was given.";
			break;
	}


	objectSprite.setTexture(objectTexture);
}


/*
* <DESCRIPTION>
* completes the construction of a buildable game object.
*/
void GameObject::completeConstruction(){
	delete materialList;
	objectSprite.setColor(Color(255, 255, 255, 255));
	triggerType = TriggerType::No_Action;
}