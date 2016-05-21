#include "MaterialList.h"

/*
* <DESCRIPTION>
* Constructor for the MaterialList class
* It will call the method to set the values for the material list.
*
* @PARAMS
* buildAbleObject: GameObjectType enum value of the buildable game object to decude the material list
*/
MaterialList::MaterialList(GameObjectType buildAbleObject)
{
	setMaterialList(buildAbleObject);
}


MaterialList::~MaterialList()
{
}

/*
* @RETURNS
* returns a vector contaning all the materials still required for the construction
*/
vector<Material*> MaterialList::getMaterialList(){
	return materialList;
}


/*
* <DESCRIPTION>
* sets the materialList vector depending on what type of constructable game object the list is for.
*
* @PARAMS
* buildAbleObject: GameObjectType enum that represents what kind of material list this object
* will be representing.
*/
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


/*
* <DESCRIPTION>
* Adds the any items in the player inventory to the construction as long as the materials
* matches eachother.
*
* @PARAMS
* playerInventory: pointer to the Inventory object contained in the player class.
*/
void MaterialList::addItemsToConstruction(Player *player){
	
	//If there is no remaning AP then the player cant add anything to the construction
	if (player->StatsManager()->getRemaningActionPoints() <= 0){
		return;
	}
	for (unsigned int i = 0; i < player->InventoryManager()->getInventoryItems().size(); ++i){
		//If the slot is empty then the next slot will be checked.
		if (player->InventoryManager()->getInventoryItems()[i]->getType() == GameObjectType::None){
			continue;
		}

		for (unsigned int j = 0; j < materialList.size(); ++j){
			if (player->InventoryManager()->getInventoryItems()[i]->getType() == materialList[j]->getMaterialType()){
					
				if (player->InventoryManager()->getInventoryItems()[i]->isStackAble()){

					//if the player has more than enough of the required material
					if (player->InventoryManager()->getInventoryItems()[i]->getStackAmount() > materialList[j]->getAmountRequired()){

						//if the player has enough AP
						if (player->StatsManager()->getRemaningActionPoints() >= materialList[j]->getAmountRequired()){

							player->InventoryManager()->getInventoryItems()[i]->reduceStackAmount(materialList[j]->getAmountRequired());
							player->StatsManager()->ConsumeActionPoints(materialList[j]->getAmountRequired());
							removeMaterialFromList(j);
						}
						//else amount if removed based on remaning AP
						else{
							reduceMaterialsBasedOnAP(player, i, j);
						}
						
					}

					//else if the player has not enough of the required material
					else if (player->InventoryManager()->getInventoryItems()[i]->getStackAmount() < materialList[j]->getAmountRequired()){

						//if the player has enough AP to add material to the construction
						if (player->StatsManager()->getRemaningActionPoints() >= player->InventoryManager()->getInventoryItems()[i]->getStackAmount()){
							materialList[j]->reduceAmountRequired(player->InventoryManager()->getInventoryItems()[i]->getStackAmount());
							player->StatsManager()->ConsumeActionPoints(player->InventoryManager()->getInventoryItems()[i]->getStackAmount());
							player->InventoryManager()->removeInventoryItem(i);
						}
						//else amount if removed based on remaning AP
						else {
							reduceMaterialsBasedOnAP(player, i, j);
						}
						
					}
					//else the player has the exact amount of the required material.
					else{
						//if the player has enough AP to add to the construction
						if (player->StatsManager()->getRemaningActionPoints() >= materialList[j]->getAmountRequired()){
							player->StatsManager()->ConsumeActionPoints(materialList[j]->getAmountRequired());
							removeMaterialFromList(j);
							player->InventoryManager()->removeInventoryItem(i);
						}
						//else amount if removed based on remaning AP
						else {
							reduceMaterialsBasedOnAP(player, i, j);
						}
						
					}
				}

				else {
					//TODO:add unique item to construction and remove Ap
				}
				
				//Item has been found and the next material should be looked for.
				break;
			}
		}
		
	}
}

/*
* <DESCRIPTION>
* Removes the required items in the material list based on remaning action points
*
* @PARAMS
* player: pointer to the Player object
* inventoryIndex: index in the inventory for the material being consumed.
* materialListIndex: index of the material being consumed in the material list.
*/
void MaterialList::reduceMaterialsBasedOnAP(Player *player, int inventoryIndex, int materialListIndex){
	player->InventoryManager()->getInventoryItems()[inventoryIndex]->reduceStackAmount(player->StatsManager()->getRemaningActionPoints());
	materialList[materialListIndex]->reduceAmountRequired(player->StatsManager()->getRemaningActionPoints());
	player->StatsManager()->ConsumeActionPoints(player->StatsManager()->getRemaningActionPoints());
}

/*
* <DESCRIPTION>
* removes a material from the list by index.
*
* @PARAMS
* index: integer representing the vector position to remove from the material list.
*/
void MaterialList::removeMaterialFromList(int index){
	//free up stack memory
	delete materialList[index];

	//removes pointer
	materialList.erase(materialList.begin() + index);
}
