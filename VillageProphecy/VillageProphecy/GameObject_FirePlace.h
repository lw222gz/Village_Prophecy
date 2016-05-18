#pragma once
#include "IGameObject.h"

class GameObject_FirePlace : public IGameObject
{
public:
	GameObject_FirePlace(Vector2f pos, Texture *FirePlaceTexture, Texture *BurningFirePlaceTexture);
	~GameObject_FirePlace();

	Sprite getSprite();
	TriggerType getTriggerType();
	GameObjectType getObjectType();
	MaterialList *MaterialListManager();
	void completeConstruction();

	//TODO: Refactor and break up gameobjects to diffrent classes.
	//due to polymorphism is needed.
	void firePlaceBurnOut();
	void setOnFire();
	

private:
	//amount of days a fireplace lasts before a new one needs to be constructed.
	const int firePlaceLifeTime = 3;
	int firePlaceDaysLasted = 0;

	MaterialList *materialList = NULL;
	GameObjectType type = Fireplace;

	Texture FirePlaceTexture;
	Texture BurningFirePlaceTexture;
};

