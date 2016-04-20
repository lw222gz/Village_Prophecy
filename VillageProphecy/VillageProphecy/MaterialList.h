#pragma once
//#include "ObjectType.h"
#include "Material.h"
#include "Inventory.h"
#include "Player.h"
//#include <vector>

//http://stackoverflow.com/questions/6515143/user-created-header-causing-c2061-syntax-error-identifier-classname
class Player;
class Material; //Forward decleration

using namespace std;

class MaterialList
{
public:
	MaterialList(GameObjectType buildAbleObject);
	~MaterialList();
	vector<Material*> getMaterialList();

	void addItemsToConstruction(Player *player);



private:
	vector<Material*> materialList;
	void setMaterialList(GameObjectType buildAbleObject);
	void removeMaterialFromList(int index);

	void reduceMaterialsBasedOnAP(Player *player, int inventoryIndex, int materialListIndex);
};

