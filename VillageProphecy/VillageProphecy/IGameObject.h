#pragma once
#include "TriggerType.h"
#include "ObjectType.h"
#include "MaterialList.h"
#include "IDrawAble.h"

class Player;


class IGameObject : public IDrawAble {
public:
	bool isTriggerd(Player *p);
	virtual TriggerType getTriggerType() = 0;
	virtual GameObjectType getObjectType() = 0;

	//TODO: the following methods are type specific and should not be required
	//to be included by every derived class. This needs to be fixed.
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