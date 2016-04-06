#include "GameItem.h"


GameItem::GameItem(ItemType gameItemType) : itemType(gameItemType)
{
	if (!emptySlotTexture.loadFromFile("Textures/PHInventorySpot.png")){
		throw "InventorySpot texture did not load correctly.";
	}
	setItemSprite();
}


GameItem::~GameItem()
{
}

Sprite GameItem::getSprite(){
	return itemSprite;
}

//sets the item sprite depending on the item type
void GameItem::setItemSprite(){
	switch (itemType){
		case ItemType::Empty:
			itemSprite.setTexture(emptySlotTexture);
			break;

		default:
			//default texture is empty slot in case of buggs or texture not finished/ implemented
			itemSprite.setTexture(emptySlotTexture);
			break;
	}
}
