#pragma once
#include "GameItem.h"
//#include "ObjectType.h"
#include "MaterialList.h"


using namespace std;

class Inventory 
{
public:
	Inventory(TextureLoader *_textures);
	~Inventory();
	void addItem(GameItem *item);
	vector<GameItem*> getInventoryItems();	
	void removeInventoryItem(int index);
	

private:
	TextureLoader *textures;
	vector<GameItem*> inventoryItems;
};

