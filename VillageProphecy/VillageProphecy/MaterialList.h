#pragma once
//#include "ObjectType.h"
#include "Material.h"
#include "Inventory.h"
//#include <vector>

//http://stackoverflow.com/questions/6515143/user-created-header-causing-c2061-syntax-error-identifier-classname
class Inventory;
class Material; //Forward decleration

using namespace std;

class MaterialList
{
public:
	MaterialList(GameObjectType buildAbleObject);
	~MaterialList();
	vector<Material*> getMaterialList();

	void addItemsToConstruction(Inventory *player);

private:
	vector<Material*> materialList;
	void setMaterialList(GameObjectType buildAbleObject);
	void removeMaterialFromList(int index);
};

