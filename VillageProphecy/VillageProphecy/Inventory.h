#pragma once
#include "GameItem.h"
//#include "ObjectType.h"
#include "MaterialList.h"


using namespace std;

class Inventory 
{
public:
	Inventory();
	~Inventory();
	void addItem(GameItem *item);
	vector<GameItem*> getInventoryItems();	
	void removeInventoryItem(int index);
	

private:
	vector<GameItem*> inventoryItems;
};

