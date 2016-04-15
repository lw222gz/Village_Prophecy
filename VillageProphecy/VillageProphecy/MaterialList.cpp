#include "MaterialList.h"


MaterialList::MaterialList(GameObjectType buildAbleObject)
{
	setMaterialList(buildAbleObject);
}


MaterialList::~MaterialList()
{
}

vector<Material*> MaterialList::getMaterialList(){
	return materialList;
}


void MaterialList::setMaterialList(GameObjectType buildAbleObject){
	switch (buildAbleObject)
	{
		case GameObjectType::Fireplace:
			materialList.push_back(new Material(GameObjectType::Tree, 2));
			break;
	

		default:
			//throw "Game was trying to create a buildable object that is not buildable.";
			break;
	}
}


void MaterialList::addItemsToConstruction(Inventory *playerInventory){

	for (int i = 0; i < playerInventory->getInventoryItems().size(); ++i){
		//If the slot is empty then the next slot will be checked.
		if (playerInventory->getInventoryItems()[i]->getType() == GameObjectType::None){
			continue;
		}

		for (int j = 0; j < materialList.size(); ++j){
			if (playerInventory->getInventoryItems()[i]->getType() == materialList[j]->getMaterialType()){

				if (playerInventory->getInventoryItems()[i]->isStackAble()){

					if (playerInventory->getInventoryItems()[i]->getStackAmount() > materialList[j]->getAmountRequired()){
						//TODO: remove the required material and reduce player stack amount.
						playerInventory->getInventoryItems()[i]->reduceStackAmount(materialList[j]->getAmountRequired());

						removeMaterialFromList(j);
					}
					else if (playerInventory->getInventoryItems()[i]->getStackAmount() < materialList[j]->getAmountRequired()){
						materialList[j]->reduceAmountRequired(playerInventory->getInventoryItems()[i]->getStackAmount());

						playerInventory->removeInventoryItem(i);
						//TODO: remove the item from the player inventory and reduce the required material amount
					}
					else{
						removeMaterialFromList(j);
						playerInventory->removeInventoryItem(i);
						//remove the item in the player inventory aswell as the required material.
					}
				}

				else {
					//TODO:add unique item to construction
				}
				
				//Item has been found and the next material should be looked for.
				break;
			}
		}
		
	}
}


//removes a required material from the list by index
void MaterialList::removeMaterialFromList(int index){
	//free up stack memory
	delete materialList[index];

	//removes pointer
	materialList.erase(materialList.begin() + index);
}
