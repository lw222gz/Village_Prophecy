#pragma once
#include "ItemType.h"
#include "IDrawAble.h"

class GameItem : public IDrawAble
{
public:
	GameItem(ItemType itemType);
	~GameItem();	
	Sprite getSprite();
	void setSlotPosition(Vector2f);

private:
	ItemType itemType;
	Sprite itemSprite;
	Texture emptySlotTexture;
	void setItemSprite();

};

