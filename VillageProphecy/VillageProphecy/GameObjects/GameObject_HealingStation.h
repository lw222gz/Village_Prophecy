#pragma once
#include "../BaseClasses/IGameObject.h"

class GameObject_HealingStation : public IGameObject
{
public:
	GameObject_HealingStation(Vector2f pos, Texture *_HealingStationTexture);
	~GameObject_HealingStation();

	Sprite getSprite();
	TriggerType getTriggerType();
	GameObjectType getObjectType();	
	GameObjectType getConsumptionType();

	MaterialList *MaterialListManager();
	void completeConstruction();
	void setOnFire();
};

