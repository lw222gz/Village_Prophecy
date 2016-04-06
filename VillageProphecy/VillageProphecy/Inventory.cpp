#include "Inventory.h"

Inventory::Inventory() 
{
	//set amount of inventory spots
	inventoryItems.reserve(6);
	//TODO: Create empty inventory spots.
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