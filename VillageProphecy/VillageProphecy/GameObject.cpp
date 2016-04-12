#include "GameObject.h"


GameObject::GameObject(GameObjectType objectType, Vector2f pos) : type(objectType)
{
	objectSprite.setPosition(pos);
	setObjectSprite();
}


GameObject::~GameObject()
{
}

//returns object type
GameObjectType GameObject::getObjectType(){
	return type;
}


Sprite GameObject::getSprite(){
	return objectSprite;
}

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

//returns the type of action that will happen when the player triggers the object
TriggerType GameObject::getTriggerType(){
	return triggerType;
}

//Sets the texture of the game object aswell as it's trigger type. 
void GameObject::setObjectSprite(){
	switch (type){
		case GameObjectType::Tree:
			//TODO: set texture
			if (!objectTexture.loadFromFile("Textures/PHWoodObject.png")){
				throw "Game object Wood textures did not load correctly.";
			}
			triggerType = TriggerType::Harvest;
			break;

		default:
			//To possible bugg check I will use the empty inventory slot texture
			//as default.
			if (!objectTexture.loadFromFile("Textures/PHInventorySpot.png")){
				throw "Defualt texture for a new gameobject did not load correctly.";
			}
			//Default trigger type will be No_Action, then nothing will happen on trigger
			triggerType = TriggerType::No_Action;
			break;
	}


	objectSprite.setTexture(objectTexture);
}
