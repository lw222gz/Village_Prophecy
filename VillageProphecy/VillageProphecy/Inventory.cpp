#include "Inventory.h"

Inventory::Inventory() 
{
	//set amount of inventory spots
	inventoryItems.reserve(6);
	//TODO: Create empty inventory spots.
	for (int i = 0; i < 6; i++){
		inventoryItems.push_back(new GameItem(GameObjectType::None));
	}
}


Inventory::~Inventory()
{
}

//add a gameitem to the player inventory
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

//Gets the players inventory items
vector<GameItem*> Inventory::getInventoryItems(){
	return inventoryItems;
}


//removes pointer and frees up memory 
void Inventory::removeInventoryItem(int index){
	delete inventoryItems[index];

	//makes the inventory spot empty
	inventoryItems[index] = new GameItem(GameObjectType::None);
}