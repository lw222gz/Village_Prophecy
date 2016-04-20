#include "Material.h"

/*
* <DESCRIPTION>
* Constructor for the Material class
* 
* @PARAMS
* type: GameObjectType enum value that represents the type of the material item, this type has
* to be lootable.
* amount: integer representing the amount of the required material is required for the construction
*/
Material::Material(GameObjectType type, int amount) : materialType(type), amountRequired(amount)
{
}


Material::~Material()
{
}

/*
* @RETURNS
* returns the material GameObjectType.
*/
GameObjectType Material::getMaterialType(){
	return materialType;
}

/*
* @RETURNS
* returns the amount still required to do the construction of the object
*/
int Material::getAmountRequired(){
	return amountRequired;
}

/*
* <DESCRIPTION>
* reduces the amount required with the given integer value. 
* If the amount to be removed is bigger than the total amount still required for the 
* gameobject to be constructed an error is thrown.
*
* @PARAMS
* amount: integer value representing the amount of this material that was just added to the construction.
*/
void Material::reduceAmountRequired(int amount){
	if (amount > amountRequired){
		throw "Amount to remove is too high";
	}
	amountRequired -= amount;
}