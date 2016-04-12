#pragma once
#include "ObjectType.h"
#include "IDrawAble.h"
#include "Player.h"
#include "TriggerType.h"
#include <SFML/Graphics.hpp>


using namespace sf;

class GameObject : public IDrawAble
{
public:
	GameObject(GameObjectType objectType, Vector2f pos);
	~GameObject();
	Sprite getSprite();
	bool isTriggerd(Player *p);
	TriggerType getTriggerType();
	GameObjectType getObjectType();

private:
	TriggerType triggerType = TriggerType::No_Action;
	float triggerRange = 50;
	GameObjectType type;
	Sprite objectSprite;
	Texture objectTexture;
	void setObjectSprite();
};

