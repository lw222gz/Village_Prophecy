#include "GameItem.h"

/*
* <DESCRIPTION>
* GameItem constructor.
* Loads in the textures for any game items and calls the setItemSprite function
*
* @PARAMS
* objectType: GameObjectType enum value representing the kind of item that is being created.
*/
GameItem::GameItem(GameObjectType objectType, TextureLoader *_textures) 
	: itemType(objectType), textures(_textures)
{
	setItemSprite();
}


GameItem::~GameItem()
{
}

/*
* @RETURNS
* returns the item sprite
*/
Sprite GameItem::getSprite(){
	return SlotSprite;
}

/*
* @RETURNS
* returns GameObjectType enum value representing the item type
*/
GameObjectType GameItem::getType(){
	return itemType;
}

/*
* @RETURNS
* if the item is stackable the amount in the stack is returned, otherwise returns 0
*/
int GameItem::getStackAmount(){
	if (stackAble){
		return stackAmount;
	}
	else {
		return 0;
	}
}

/*
* @RETURNS
* returns boolean, true if the item is stackable, otherwise false.
*/
bool GameItem::isStackAble(){
	return stackAble;
}

/*
* <DESCRIPTION>
* Adds 1 amount to the stack of the item if it's stackable.
*/
void GameItem::addToStack(){
	if (stackAble){
		stackAmount += 1;
	}	
}


/*
* <DESCRIPTION>
* Removes X amount from a stackable item.
*
* @PARAMS
* amount: integer representing the amount to be removed, 
* if this is heigher than the stack amount an error is thrown
*/
void GameItem::reduceStackAmount(int amount){
	if (amount > stackAmount){
		throw "Amount to remove from stack is too high";
	}
	stackAmount -= amount;
}

/*
* <DESCRIPTION>
* Sets the sprite for the item based 
*/
void GameItem::setItemSprite(){
	switch (itemType){
		case GameObjectType::None:		
			SlotTexture = *textures->getEmptyInventorySlotTexture();
			stackAble = false;
			break;

		case GameObjectType::Tree:		
			SlotTexture = *textures->getWoodSlotTexture();
			stackAble = true;
			break;

		default:
			throw "GAME ITEM ERROR: Game item type is not a vaild inventory type.";
			break;
	}

	SlotSprite.setTexture(SlotTexture);
}
