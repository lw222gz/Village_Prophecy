#include "GameObject.h"


GameObject::GameObject(GameObjectType objectType, Vector2f pos) : type(objectType)
{
	objectSprite.setPosition(pos);
	setObjectSprite();
}


GameObject::~GameObject()
{
}


Sprite GameObject::getSprite(){
	return objectSprite;
}

bool GameObject::isTriggerd(Player *p){
	if (p->getPosition().x + p->getSize().x >= objectSprite.getPosition().x - triggerRange &&
		p->getPosition().x <= objectSprite.getPosition().x + objectTexture.getSize().x + triggerRange){
		//TODO: add Y collosion
		return true;
	}
	else{
		return false;
	}
}

void GameObject::TriggerdEffect(){

}


void GameObject::setObjectSprite(){
	switch (type){
		case GameObjectType::Tree:
			//TODO: set texture
			if (!objectTexture.loadFromFile("Textures/PHWoodObject.png")){
				throw "Game object Wood textures did not load correctly.";
			}
			break;

		default:
			//To possible bugg check I will use the empty inventory slot texture
			//as default.
			if (!objectTexture.loadFromFile("Textures/PHInventorySpot.png")){
				throw "Defualt texture for a new gameobject did not load correctly.";
			}
			break;
	}


	objectSprite.setTexture(objectTexture);
}
