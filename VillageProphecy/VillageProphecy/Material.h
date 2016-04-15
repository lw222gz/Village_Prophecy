#pragma once
#include "ObjectType.h"

class Material
{
public:
	Material(GameObjectType type, int amount);
	~Material();
	GameObjectType getMaterialType();
	int getAmountRequired();
	void reduceAmountRequired(int amount);

private:
	GameObjectType materialType;
	int amountRequired;
};

