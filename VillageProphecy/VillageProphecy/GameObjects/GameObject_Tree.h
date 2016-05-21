#pragma once
#include "../BaseClasses/IGameObject.h"

class GameObject_Tree : public IGameObject
{
public:
	GameObject_Tree(Vector2f pos, Texture *TreeTexture);
	~GameObject_Tree();

	Sprite getSprite();
	TriggerType getTriggerType();
	GameObjectType getObjectType();
	MaterialList *MaterialListManager();

	GameObjectType getConsumptionType();
	void completeConstruction();
	void setOnFire();
};

