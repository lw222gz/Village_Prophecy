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
	//TODO: check the problem that occured when the texture is static
	//It crashed the game
	Texture emptySlotTexture;
	void setItemSprite();

};

