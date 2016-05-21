#pragma once
#include "../Enums/TriggerType.h"
#include "../Enums/ObjectType.h"
#include "../GameObjects/ObjectMaterials/MaterialList.h"
#include "IDrawAble.h"

class Player;


class IGameObject : public IDrawAble {
public:
	bool isTriggerd(Player *p);
	virtual TriggerType getTriggerType() = 0;
	virtual GameObjectType getObjectType() = 0;

	//TODO: the following methods are type specific and should not be required
	//to be included by every derived class. This needs to be fixed.
	virtual GameObjectType getConsumptionType() = 0;
	virtual MaterialList *MaterialListManager() = 0;
	virtual void completeConstruction() = 0;
	virtual void setOnFire() = 0;

	//this does not need to be declared?
	//virtual Sprite getSprite() = 0;

protected:
	const float triggerRange = 20;
	Sprite objectSprite;
	TriggerType triggerType = No_Action;

};