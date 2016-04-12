#pragma once
#include "GameItem.h"
#include "ObjectType.h"
#include <vector>

using namespace std;

class Inventory 
{
public:
	Inventory();
	~Inventory();
	void addItem(GameItem *item);
	vector<GameItem*> getInventoryItems();	

private:
	vector<GameItem*> inventoryItems;
};

