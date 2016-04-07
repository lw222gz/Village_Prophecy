#include "Inventory.h"

Inventory::Inventory() 
{
	//set amount of inventory spots
	inventoryItems.reserve(6);
	//TODO: Create empty inventory spots.
	for (int i = 0; i < 6; i++){
		inventoryItems.push_back(new GameItem(ItemType::Empty));
	}
}


Inventory::~Inventory()
{
}

//add a gameitem to the player inventory
void Inventory::addItem(GameItem *item){
	//TODO: add the item to the list aslong as there does not allready exist 6 items in the inventory
}

//Gets the players inventory items
vector<GameItem*> Inventory::getInventoryItems(){
	return inventoryItems;
}