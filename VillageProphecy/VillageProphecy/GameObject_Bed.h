#pragma once
#include "IGameObject.h"


class GameObject_Bed : public IGameObject
{
public:
	GameObject_Bed(Vector2f pos, Texture *_BedTexture);
	~GameObject_Bed();


	Sprite getSprite();
	TriggerType getTriggerType();
	GameObjectType getObjectType();
	MaterialList *MaterialListManager();

	void completeConstruction();
	void setOnFire();

private:
};

