#include "GameItem.h"


GameItem::GameItem(GameObjectType objectType) : itemType(objectType)
{
	if (!emptySlotTexture.loadFromFile("Textures/PHInventorySpot.png")){
		throw "TEXTURE LOAD ERROR: InventorySpot texture did not load correctly.";
	}
	if (!woodSlotTexture.loadFromFile("Textures/PHWoodSlotTexture.png")){
		throw "TEXTURE LOAD ERROR: Wood slot texture did not load correctly.";
	}
	setItemSprite();
}


GameItem::~GameItem()
{
}

//sets the visual position of an item slot.
void GameItem::setSlotPosition(Vector2f pos){
	itemSprite.setPosition(pos);
}

Sprite GameItem::getSprite(){
	return itemSprite;
}

//Returns the item type.
GameObjectType GameItem::getType(){
	return itemType;
}

int GameItem::getStackAmount(){
	if (stackAble){
		return stackAmount;
	}
	else {
		return 0;
	}
}

bool GameItem::isStackAble(){
	return stackAble;
}

void GameItem::addToStack(){
	stackAmount += 1;
}

//sets the item sprite depending on the item type
void GameItem::setItemSprite(){
	switch (itemType){
		case GameObjectType::None:
			itemSprite.setTexture(emptySlotTexture);
			stackAble = false;
			break;

		case GameObjectType::Tree:
			itemSprite.setTexture(woodSlotTexture);
			stackAble = true;
			break;

		default:
			throw "GAME ITEM ERROR: Game item type is not a vaild inventory type.";
			break;
	}
}
