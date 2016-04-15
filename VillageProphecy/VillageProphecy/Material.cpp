#include "Material.h"


Material::Material(GameObjectType type, int amount) : materialType(type), amountRequired(amount)
{
}


Material::~Material()
{
}


GameObjectType Material::getMaterialType(){
	return materialType;
}

int Material::getAmountRequired(){
	return amountRequired;
}


void Material::reduceAmountRequired(int amount){
	if (amount > amountRequired){
		throw "Amount to remove is too high";
	}
	amountRequired -= amount;
}