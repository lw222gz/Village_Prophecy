#pragma once
#include "GameItem.h"
//#include "ObjectType.h"
#include "../GameObjects/ObjectMaterials/MaterialList.h"


using namespace std;

class Inventory 
{
public:
	Inventory(TextureLoader *_textures);
	~Inventory();
	void addItem(GameItem *item);
	vector<GameItem*> getInventoryItems();	
	void removeInventoryItem(int index);
	bool PlayerHasItem(GameObjectType itemType);
	void ConsumeInventoryItem(GameObjectType itemType);
	

private:
	TextureLoader *textures;
	vector<GameItem*> inventoryItems;

	int getItemIndex(GameObjectType itemType);
};

