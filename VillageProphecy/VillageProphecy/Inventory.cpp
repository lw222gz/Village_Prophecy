#include "Inventory.h"

/*
* <DESCRIPTION>
* Inventory class constructor.
* Initiates the inventory with empty slots.
*
* @PARAMS
* _textures: pointer to the TextureLoader class that contains all the textures
*/
Inventory::Inventory(TextureLoader *_textures)
	: textures(_textures)
{
	//set amount of inventory spots
	inventoryItems.reserve(6);
	//TODO: Create empty inventory spots.
	for (int i = 0; i < 6; i++){
		inventoryItems.push_back(new GameItem(GameObjectType::None, textures));
	}
}


Inventory::~Inventory()
{
}

/*
* <DESCRIPTION>
* Add a gameitem to the inventory
*
* @PARAMS
* item: pointer to a gameitem object
*/
void Inventory::addItem(GameItem *item){
	int inventoryIndex = -1;
	for (int i = 0; i < inventoryItems.size(); ++i){
		if (item->isStackAble()){
			if (inventoryItems[i]->getType() == item->getType()){
				//if added to stack the stack will get +1 and then leave the
				//so the delete doesnt run after the loop.
				inventoryItems[i]->addToStack();
				return;
			}
			if (inventoryItems[i]->getType() == GameObjectType::None && inventoryIndex == -1){
				inventoryIndex = i;
			}
		}
		//If a gameitem isent stackable the first avalible emptyslot is checked up.
		else if (inventoryItems[i]->getType() == GameObjectType::None){
			inventoryIndex = i;
			break;
		}
	}

	//If a free inventory spot was found then it gets replaced with a new item.
	if (inventoryIndex > -1){
		delete inventoryItems[inventoryIndex];
		inventoryItems[inventoryIndex] = item;
	}
	//else the inventory is full.
	else{
		//NO FREE SPOT WAS FOUND! 
		//TODO: Abort looting gameobject
	}
}

/*
* @RETURNS
* returns the inventory vector.
*/
vector<GameItem*> Inventory::getInventoryItems(){
	return inventoryItems;
}


/*
* <DESCRIPTION>
* Removes an item in the inventory by index.
*
* @PARAMS
* index: int value representing the position to remove in the vector.
*/
void Inventory::removeInventoryItem(int index){
	delete inventoryItems[index];

	//makes the inventory spot empty
	inventoryItems[index] = new GameItem(GameObjectType::None, textures);
}