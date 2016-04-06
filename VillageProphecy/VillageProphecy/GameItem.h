#pragma once
#include "ItemType.h"
#include "IDrawAble.h"

class GameItem : public IDrawAble
{
public:
	GameItem(ItemType itemType);
	~GameItem();	
	Vector2f getPosition();
	Sprite getSprite();

private:
	ItemType itemType;
	Sprite itemSprite;
	static Texture emptySlotTexture;
	void setItemSprite();

};

